#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);

    // Create a REQ (Request) socket connected to the server
    zmq::socket_t socket(context, zmq::socket_type::req);
    socket.connect("tcp://localhost:5555");

    std::string message = "Hello from the consumer!";
    zmq::message_t request(message.data(), message.size());

    // Send a request to the server
    socket.send(request, zmq::send_flags::none);

    zmq::message_t reply;

    // Receive the reply from the server
    auto r=socket.recv(reply, zmq::recv_flags::none);
    std::string response(static_cast<char*>(reply.data()), reply.size());
    std::cout << "Received reply: " << response << std::endl;

    return 0;
}

