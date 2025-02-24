#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);

    // Create a REP (Reply) socket bound to a specific address
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        // Wait for the client to send a request
        auto r=socket.recv(request, zmq::recv_flags::none);
        std::string msg(static_cast<char*>(request.data()), request.size());
        std::cout << "Received request: " << msg << std::endl;

        // Send a reply back to the client
        std::string reply = "Hello from the producer!";
        zmq::message_t response(reply.data(), reply.size());
        socket.send(response, zmq::send_flags::none);
    }

    return 0;
}

