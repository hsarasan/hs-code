#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t dealer(context, zmq::socket_type::dealer);
    dealer.connect("tcp://localhost:5555");

    for (int i = 0; i < 5; i++) {
        std::string request = "Request #" + std::to_string(i);
        dealer.send(zmq::message_t(request), zmq::send_flags::none);
        std::cout << "Sent: " << request << std::endl;

        zmq::message_t reply;
        dealer.recv(reply, zmq::recv_flags::none);
        std::cout << "Received: " << std::string(static_cast<char*>(reply.data()), reply.size()) << std::endl;
    }

    return 0;
}
