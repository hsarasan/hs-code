#include <zmq.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);

    // Create a PUB (Publisher) socket bound to a specific address
    zmq::socket_t socket(context, zmq::socket_type::pub);
    socket.bind("tcp://*:5556");

    std::this_thread::sleep_for(std::chrono::seconds(1));  // Give subscribers time to connect

    int count = 0;
    while (true) {
        // Define the topic
        std::string topic = "news";  // Change this to any topic, e.g., "sports", "finance", etc.

        // Create the message: "topic content"
        std::string message = topic + " Message #" + std::to_string(count++);
        zmq::message_t msg(message.data(), message.size());

        // Send the message to subscribers
        socket.send(msg, zmq::send_flags::none);
        std::cout << "Sent: " << message << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait before sending the next message
    }

    return 0;
}
