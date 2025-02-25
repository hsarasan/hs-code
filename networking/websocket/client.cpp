#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>
#include <chrono>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        websocket::stream<tcp::socket> ws(ioc);

        auto const results = resolver.resolve("localhost", "9002");
        net::connect(ws.next_layer(), results.begin(), results.end());

        ws.handshake("localhost", "/");  // Perform WebSocket handshake
        std::cout << "Connected to server\n";

        beast::flat_buffer buffer;
        for (int i = 1; i <= 5; ++i) {  // Loop for 5 iterations
            std::string message = "Client message " + std::to_string(i);
            std::cout << "Sending: " << message << std::endl;
            ws.write(net::buffer(message));

            for (int j = 0; j < 4; ++j) {  // Expect 4 responses per iteration
                ws.read(buffer);
                std::cout << "Received: " << beast::buffers_to_string(buffer.data()) << std::endl;
                buffer.consume(buffer.size());
            }
					std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "Closing connection\n";
        ws.close(websocket::close_code::normal);
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
}
