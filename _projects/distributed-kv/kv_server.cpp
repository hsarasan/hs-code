#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <thread>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;
namespace http = boost::beast::http;
namespace json = nlohmann;

class KVStore {
public:
    KVStore(const std::string& wal_dir, const std::string& wal_filename, const std::vector<std::pair<std::string, int>>& peers)
        : peers(peers), wal_dir(wal_dir), wal_filename(wal_filename) {
        load_wal();
    }

    std::string get_value(const std::string& key) {
        std::lock_guard<std::mutex> lock(store_mutex);
        if (kv_store.find(key) != kv_store.end()) {
            return kv_store[key];
        } else {
            return "Key not found!";
        }
    }

    void set_value(const std::string& key, const std::string& value) {
        {
            std::lock_guard<std::mutex> lock(store_mutex);
            kv_store[key] = value;
        }
        log_wal("SET", key, value);
        replicate("SET", key, value);
    }

    void delete_value(const std::string& key) {
        {
            std::lock_guard<std::mutex> lock(store_mutex);
            kv_store.erase(key);
        }
        log_wal("DELETE", key, "");
        replicate("DELETE", key, "");
    }

    void update_value(const std::string& key, const std::string& value) {
        {
            std::lock_guard<std::mutex> lock(store_mutex);
            kv_store[key] = value;
        }
        log_wal("UPDATE", key, value);
        replicate("UPDATE", key, value);
    }

private:
    std::unordered_map<std::string, std::string> kv_store;
    std::vector<std::pair<std::string, int>> peers;
    std::mutex store_mutex;
    std::string wal_dir, wal_filename;

    void load_wal() {
        std::ifstream wal_file(wal_dir + "/" + wal_filename);
        std::string line;
        while (std::getline(wal_file, line)) {
            std::stringstream ss(line);
            std::string operation, key, value;
            ss >> operation >> key;
            std::getline(ss, value);
            if (operation == "SET" || operation == "UPDATE") {
                kv_store[key] = value;
            } else if (operation == "DELETE") {
                kv_store.erase(key);
            }
        }
    }

    void log_wal(const std::string& operation, const std::string& key, const std::string& value) {
        std::ofstream wal_file(wal_dir + "/" + wal_filename, std::ios_base::app);
        wal_file << operation << " " << key << " " << value << "\n";
    }

    void replicate(const std::string& operation, const std::string& key, const std::string& value) {
        for (const auto& peer : peers) {
            std::thread([peer, operation, key, value]() {
                try {
                    boost::asio::io_context ioc;
                    tcp::resolver resolver(ioc);
                    tcp::socket socket(ioc);

                    auto endpoints = resolver.resolve(peer.first, std::to_string(peer.second));
                    boost::asio::connect(socket, endpoints);

                    json::json request_json = {{"operation", operation}, {"key", key}, {"value", value}};
                    std::string body = request_json.dump();

                    http::request<http::string_body> req(http::verb::post, "/", 11);
                    req.set(http::field::host, peer.first);
                    req.set(http::field::content_type, "application/json");
                    req.body() = body;
                    req.prepare_payload();

                    http::write(socket, req);
                    socket.close();
                } catch (...) {
                    std::cerr << "Replication failed to " << peer.first << ":" << peer.second << std::endl;
                }
            }).detach();
        }
    }
};

struct ServerConfig {
    std::string ip_address;
    int port;
    std::string wal_directory;
    std::string wal_filename;
    std::vector<std::pair<std::string, int>> peers;
};

class KVServer {
private:
    KVStore kv_store;
    boost::asio::io_context io_service_;
    tcp::acceptor acceptor;

public:
    KVServer(const ServerConfig& config)
        : kv_store(config.wal_directory, config.wal_filename, config.peers),
          acceptor(io_service_, tcp::endpoint(boost::asio::ip::make_address(config.ip_address), config.port)) {}

    void start() {
        std::cout << "Server is running on port " << acceptor.local_endpoint().port() << std::endl;
        accept_connection();
        io_service_.run();
    }

    void accept_connection() {
        std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_service_);
        acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
            if (!ec) {
                handle_request(socket);
            }
            accept_connection();
        });
    }

void handle_request(std::shared_ptr<tcp::socket> socket) {
    try {
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(*socket, buffer, req);

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::content_type, "application/json");

        if (req.method() == http::verb::get) {
            // Extract key from the URL
            std::string key = req.target().to_string();
            if (key.front() == '/') key.erase(0, 1); // Remove leading '/'

            std::string value = kv_store.get_value(key);
            if (value == "Key not found!") {
                res.result(http::status::not_found);
                res.body() = R"({"error": "Key not found!"})";
            } else {
                res.body() = "{\"key\": \"" + key + "\", \"value\": \"" + value + "\"}";
            }
        } 
        else if (req.method() == http::verb::post || req.method() == http::verb::put) {
            json::json body_json = json::json::parse(req.body());
            std::string operation = body_json["operation"];
            std::string key = body_json["key"];
            std::string value = body_json["value"];

            if (operation == "SET") {
                kv_store.set_value(key, value);
                res.body() = R"({"message": "Value set successfully"})";
            } else if (operation == "UPDATE") {
                kv_store.update_value(key, value);
                res.body() = R"({"message": "Value updated successfully"})";
            }
        }
        else if (req.method() == http::verb::delete_) {
            std::string key = req.target().to_string();
            if (key.front() == '/') key.erase(0, 1); // Remove leading '/'
            kv_store.delete_value(key);
            res.body() = R"({"message": "Key deleted successfully"})";
        }
        else {
            res.result(http::status::bad_request);
            res.body() = R"({"error": "Invalid request method"})";
        }

        res.prepare_payload();
        http::write(*socket, res);
        socket->shutdown(tcp::socket::shutdown_send);
    } 
    catch (const std::exception& e) {
        std::cerr << "Request handling error: " << e.what() << std::endl;
    }
}


};

ServerConfig read_config(const std::string& filename) {
    std::ifstream config_file(filename);
    json::json config_json;
    config_file >> config_json;

    ServerConfig config;
    config.ip_address = config_json["ip_address"];
    config.port = config_json["port"];
    config.wal_directory = config_json["wal_directory"];
    config.wal_filename = config_json["wal_filename"];

    for (const auto& peer : config_json["peers"]) {
        config.peers.emplace_back(peer["ip"].get<std::string>(), peer["port"].get<int>());
    }

    return config;
}

int main() {
    try {
        ServerConfig config = read_config("server_config.json");

        KVServer server(config);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

