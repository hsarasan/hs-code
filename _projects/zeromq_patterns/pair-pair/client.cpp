#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.connect("tcp://localhost:5555");

    std::cout << "P2P Client connected...\n";

    while (true) {
        std::string message = "Hello from Client";
        socket.send(zmq::message_t(message), zmq::send_flags::none);
        std::cout << "[CLIENT] Sent: " << message << std::endl;

        // Receive response
        zmq::message_t reply;
        socket.recv(reply, zmq::recv_flags::none);
        std::cout << "[CLIENT] Received: " << std::string(static_cast<char*>(reply.data()), reply.size()) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}

