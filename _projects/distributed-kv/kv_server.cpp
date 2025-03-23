#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <vector>
#include <filesystem>
#include <sstream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace boost::asio;
using tcp = ip::tcp;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using json = nlohmann::json;
namespace fs = std::filesystem;

unordered_map<string, string> store;
mutex store_mutex;
string WAL_FILE;
vector<pair<string, string>> peer_nodes;  // Stores <IP, Port>

// 📝 Ensure WAL log directory exists
void ensure_directory_exists(const string& dir_path) {
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
    }
}

// 📖 Read configuration file (INI-like format)
bool read_config(const string& filename, short &port, string &wal_dir, string &wal_file, vector<pair<string, string>> &peers) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open config file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("port") != string::npos) {
            port = stoi(line.substr(line.find("=") + 1));
        } else if (line.find("wal_directory") != string::npos) {
            wal_dir = line.substr(line.find("=") + 1);
        } else if (line.find("wal_file") != string::npos) {
            wal_file = line.substr(line.find("=") + 1);
        } else if (line.find("nodes") != string::npos) {
            string peers_str = line.substr(line.find("=") + 1);
            stringstream ss(peers_str);
            string peer;
            while (getline(ss, peer, ',')) {
                size_t colon = peer.find(":");
                if (colon != string::npos) {
                    string ip = peer.substr(0, colon);
                    string port = peer.substr(colon + 1);
                    peers.emplace_back(ip, port);
                }
            }
        }
    }

    file.close();
    return true;
}

// 📝 Append operations to the WAL log
void append_to_log(const string& operation, const string& key, const string& value = "") {
    ofstream logFile(WAL_FILE, ios::app);
    if (logFile.is_open()) {
        logFile << operation << " " << key << " " << value << endl;
        logFile.close();
    }
}

// 🔄 Restore in-memory store from WAL log
void restore_from_log() {
    ifstream logFile(WAL_FILE);
    string operation, key, value;
    while (logFile >> operation >> key) {
        if (operation == "SET" || operation == "UPDATE") {
            logFile >> value;
            store[key] = value;
        } else if (operation == "DELETE") {
            store.erase(key);
        }
    }
}

// 🔍 Forward request to peer nodes if key not found
string forward_get_request(const string& key) {
    for (const auto& [peer_ip, peer_port] : peer_nodes) {
        try {
            io_context ioc;
            tcp::resolver resolver(ioc);
            auto const results = resolver.resolve(peer_ip, peer_port);

            beast::tcp_stream stream(ioc);
            stream.connect(results);

            http::request<http::string_body> req{http::verb::get, "/get/" + key, 11};
            req.set(http::field::host, peer_ip);
            req.set(http::field::user_agent, "kv_client");

            http::write(stream, req);
            beast::flat_buffer buffer;
            http::response<http::string_body> res;
            http::read(stream, buffer, res);

            if (res.result() == http::status::ok) {
                return res.body();
            }
        } catch (exception& e) {
            cerr << "Failed to connect to peer " << peer_ip << ":" << peer_port << endl;
        }
    }
    return "{}";
}

// 📌 Handle HTTP requests
void handle_request(http::request<http::string_body>& req, http::response<http::string_body>& res) {
    res.version(req.version());
    res.set(http::field::content_type, "application/json");

    if (req.method() == http::verb::post && req.target() == "/set") {
        json request_json = json::parse(req.body());
        string key = request_json["key"];
        string value = request_json["value"];

        lock_guard<mutex> lock(store_mutex);
        store[key] = value;
        append_to_log("SET", key, value);

        res.result(http::status::ok);
        res.body() = json({{"status", "OK"}}).dump();
    } 
    else if (req.method() == http::verb::get && req.target().starts_with("/get/")) {
        string key = string(req.target()).substr(5);
        lock_guard<mutex> lock(store_mutex);

        if (store.count(key)) {
            res.result(http::status::ok);
            res.body() = json({{"value", store[key]}}).dump();
        } else {
            res.result(http::status::not_found);
            res.body() = forward_get_request(key);
        }
    } 
    else if (req.method() == http::verb::delete_ && req.target().starts_with("/delete/")) {
        string key = string(req.target()).substr(8);
        lock_guard<mutex> lock(store_mutex);

        if (store.erase(key)) {
            append_to_log("DELETE", key);
            res.result(http::status::ok);
            res.body() = json({{"status", "OK"}}).dump();
        } else {
            res.result(http::status::not_found);
            res.body() = json({{"error", "Key not found"}}).dump();
        }
    } 
    else if (req.method() == http::verb::put && req.target().starts_with("/update/")) {
        string key = string(req.target()).substr(8);
        json request_json = json::parse(req.body());
        string value = request_json["value"];

        lock_guard<mutex> lock(store_mutex);

        if (store.count(key)) {
            store[key] = value;
            append_to_log("UPDATE", key, value);
            res.result(http::status::ok);
            res.body() = json({{"status", "Updated"}}).dump();
        } else {
            res.result(http::status::not_found);
            res.body() = json({{"error", "Key not found"}}).dump();
        }
    }
    else {
        res.result(http::status::bad_request);
        res.body() = json({{"error", "Invalid request"}}).dump();
    }

    res.prepare_payload();
}

// 📌 Handles an individual client session
void session(tcp::socket socket) {
    try {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        http::response<http::string_body> res;
        handle_request(req, res);

        http::write(socket, res);
    } catch (std::exception& e) {
        cerr << "Session error: " << e.what() << endl;
    }
}

// 🚀 Start the server
void run_server(short port) {
    io_context ioc;
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

    cout << "HTTP Server running on port " << port << endl;

    while (true) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);
        thread(session, move(socket)).detach();
    }
}

int main() {
    short port;
    string wal_dir, wal_file;

    if (!read_config("config.cfg", port, wal_dir, wal_file, peer_nodes)) {
        return 1;
    }

    ensure_directory_exists(wal_dir);
    WAL_FILE = wal_dir + "/" + wal_file;

    restore_from_log();
    run_server(port);
    return 0;
}

