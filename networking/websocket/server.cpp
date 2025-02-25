#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void do_session(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();  // Perform WebSocket handshake
        std::cout << "Client connected\n";

        beast::flat_buffer buffer;
        for (int i = 0; i < 5; ++i) {  // Loop for 5 iterations
            ws.read(buffer);
            std::string message = beast::buffers_to_string(buffer.data());
            std::cout << "Received: " << message << std::endl;
            buffer.consume(buffer.size());

            for (int j = 1; j <= 4; ++j) {  // Send 4 responses
                std::string response = "Response " + std::to_string(j) + " to: " + message;
                ws.text(true);
                ws.write(net::buffer(response));
            }
        }

        std::cout << "Closing connection\n";
        ws.close(websocket::close_code::normal);
    } catch (const std::exception& e) {
        std::cerr << "WebSocket session error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        net::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 9002));

        std::cout << "WebSocket server listening on ws://localhost:9002\n";

        while (true) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);
            std::thread(&do_session, std::move(socket)).detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}
