#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);

    // Create a SUB (Subscriber) socket connected to the publisher
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.connect("tcp://localhost:5556");

    // Define the topic to subscribe to
    std::string topic = "news";  // Change this to subscribe to a different topic

    // Subscribe to messages with the chosen topic
    socket.set(zmq::sockopt::subscribe, topic);

    while (true) {
        zmq::message_t message;

        // Receive a message from the publisher
        socket.recv(message, zmq::recv_flags::none);
        std::string msg(static_cast<char*>(message.data()), message.size());

        std::cout << "Received: " << msg << std::endl;
    }

    return 0;
}

