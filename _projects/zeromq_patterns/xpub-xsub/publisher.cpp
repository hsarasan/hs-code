#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.connect("tcp://localhost:5555");  // Connect to XSUB

    std::cout << "[PUBLISHER] Sending messages...\n";

    int i = 0;
    while (true) {
        std::string topic = (i % 2 == 0) ? "TopicA" : "TopicB";
        std::string message = topic + " - Message #" + std::to_string(i++);

        publisher.send(zmq::message_t(topic), zmq::send_flags::sndmore);
        publisher.send(zmq::message_t(message), zmq::send_flags::none);

        std::cout << "[PUBLISHER] Sent: " << message << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
