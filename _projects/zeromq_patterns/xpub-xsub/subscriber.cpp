#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");  // Connect to XPUB

    std::string topic = "TopicA";  // Change this to filter messages
    subscriber.set(zmq::sockopt::subscribe, topic);

    std::cout << "[SUBSCRIBER] Subscribed to: " << topic << std::endl;

    while (true) {
        zmq::message_t topic_msg, message;
        subscriber.recv(topic_msg, zmq::recv_flags::none);
        subscriber.recv(message, zmq::recv_flags::none);

        std::cout << "[SUBSCRIBER] Received: " 
                  << std::string(static_cast<char*>(message.data()), message.size()) << std::endl;
    }

    return 0;
}

