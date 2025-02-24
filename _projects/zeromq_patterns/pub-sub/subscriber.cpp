#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);

    // Create a SUB (Subscriber) socket connected to the publisher
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.connect("tcp://localhost:5556");

    // Subscribe to all messages (empty string means all messages)
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    while (true) {
        zmq::message_t message;

        // Receive a message from the publisher
        auto ret=socket.recv(message, zmq::recv_flags::none);
        std::string msg(static_cast<char*>(message.data()), message.size());

        std::cout << "Received: " << msg << std::endl;
    }

    return 0;
}
