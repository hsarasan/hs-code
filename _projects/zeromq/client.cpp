#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    // Prepare the ZeroMQ context and subscriber socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, zmq::socket_type::sub);

    // Connect to the publisher
    subscriber.connect("tcp://localhost:5555");

    // Subscribe to all messages
    subscriber.set(zmq::sockopt::subscribe, "");

    while (true) {
        // Receive a message
        zmq::message_t zmq_message;
        auto ret=subscriber.recv(zmq_message, zmq::recv_flags::none);

        // Convert message to string and print
        std::string message(static_cast<char*>(zmq_message.data()), zmq_message.size());
        std::cout << "Received: " << message << std::endl;
    }

    return 0;
}
