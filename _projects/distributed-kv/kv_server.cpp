#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <nlohmann/json.hpp>

using namespace std;
using namespace boost::asio;
using tcp = ip::tcp;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using json = nlohmann::json;

unordered_map<string, string> store;
mutex store_mutex;
const string WAL_FILE = "kv_store.log";

// 📝 Append operations to the WAL log file
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
        if (operation == "SET") {
            logFile >> value;
            store[key] = value;
        } else if (operation == "DELETE") {
            store.erase(key);
        }
    }
}

// 🔥 Periodically clean up (checkpointing)
void compact_log() {
    lock_guard<mutex> lock(store_mutex);
    ofstream snapshot("kv_store_snapshot.txt");
    for (const auto& [key, value] : store) {
        snapshot << key << " " << value << endl;
    }
    snapshot.close();
    remove(WAL_FILE.c_str()); // Delete WAL log
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
            res.body() = json({{"error", "Key not found"}}).dump();
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
    else {
        res.result(http::status::bad_request);
        res.body() = json({{"error", "Invalid request"}}).dump();
    }

    res.prepare_payload();
}

// 🌍 Handle client connections
void session(tcp::socket socket) {
    try {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        http::response<http::string_body> res;
        handle_request(req, res);
        http::write(socket, res);
    } catch (const std::exception& e) {
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
    restore_from_log();  // Restore store from WAL log on startup
    run_server(9000);
    return 0;
}

