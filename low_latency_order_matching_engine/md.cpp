#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include <mutex>

using boost::asio::ip::tcp;
using json = nlohmann::json;

// ----------------------------
// Data Structures
// ----------------------------
struct Level {
    double price;
    int qty;
};

struct OrderBook {
    std::vector<Level> bids;
    std::vector<Level> asks;
};

std::mutex mtx;
std::unordered_map<std::string, std::unordered_map<std::string, OrderBook>> market_data;

// ----------------------------
// Utility
// ----------------------------
void print_market_data() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "------ MARKET DATA ------\n";
    for (auto &ex : market_data) {
        const auto &exchange = ex.first;
        for (auto &sym_pair : ex.second) {
            const auto &symbol = sym_pair.first;
            const auto &book = sym_pair.second;
            std::cout << exchange << " " << symbol << " | Bids: ";
            for (auto &b : book.bids) std::cout << "(" << b.price << "," << b.qty << ") ";
            std::cout << "| Asks: ";
            for (auto &a : book.asks) std::cout << "(" << a.price << "," << a.qty << ") ";
            std::cout << "\n";
        }
    }
    std::cout << "-------------------------\n";
}

// ----------------------------
// Handle exchange connection
// ----------------------------
void handle_exchange(const std::string &host, int port, const std::string &exchange_name) {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(boost::asio::ip::make_address(host), port));
        std::cout << exchange_name << " connected to " << host << ":" << port << "\n";

        boost::asio::streambuf buffer;
        std::istream is(&buffer);

        while (true) {
            boost::asio::read_until(socket, buffer, "\n");
            std::string line;
            std::getline(is, line);
            if (line.empty()) continue;

            try {
                json j = json::parse(line);
                std::string symbol = j["symbol"];
                std::lock_guard<std::mutex> lock(mtx);
                OrderBook &book = market_data[exchange_name][symbol];
                book.bids.clear();
                book.asks.clear();
                for (auto &b : j["bids"])
                    book.bids.push_back({b["price"], b["qty"]});
                for (auto &a : j["asks"])
                    book.asks.push_back({a["price"], a["qty"]});
            } catch (const std::exception &e) {
                std::cerr << exchange_name << " JSON parse error: " << e.what() << "\n";
            }

            print_market_data();
        }

    } catch (const std::exception &e) {
        std::cerr << exchange_name << " connection error: " << e.what() << "\n";
    }
}

// ----------------------------
// Main
// ----------------------------
int main() {
    std::vector<std::thread> threads;

    std::unordered_map<std::string, int> exchanges = {
        {"LSE", 9001},
        {"CHIX", 9002},
        {"TRQ", 9003},
        {"BATS", 9004}
    };

    for (auto &[name, port] : exchanges) {
        threads.emplace_back(handle_exchange, "127.0.0.1", port, name);
    }

    for (auto &t : threads) t.join();

    return 0;
}
