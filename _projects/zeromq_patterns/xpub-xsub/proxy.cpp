#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);

    zmq::socket_t xsub(context, zmq::socket_type::xsub);
    xsub.bind("tcp://*:5555");  // Receive from publishers

    zmq::socket_t xpub(context, zmq::socket_type::xpub);
    xpub.bind("tcp://*:5556");  // Forward to subscribers

    std::cout << "[PROXY] XPUB-XSUB Broker Running...\n";

    zmq::proxy(xsub, xpub);  // Forward messages between PUB and SUB

    return 0;
}
