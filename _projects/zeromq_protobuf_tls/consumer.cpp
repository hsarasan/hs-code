#include <iostream>
#include <zmq.hpp>
#include "message.pb.h"

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PULL);
    socket.connect("tcp://localhost:5555");

    // Receive messages from the producer
    while (true) {
        zmq::message_t message;
        auto null_v=socket.recv(message, zmq::recv_flags::none);

        // Deserialize the received message into a Protobuf object
        Data data;
        if (data.ParseFromString(std::string(static_cast<char*>(message.data()), message.size()))) {
            std::cout << "Received message: " << data.name() << " = " << data.value() << std::endl;
        } else {
            std::cerr << "Failed to parse the incoming message." << std::endl;
        }
    }

    return 0;
}
