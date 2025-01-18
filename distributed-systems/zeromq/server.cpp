#include <zmq.hpp>
#include <zmq.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Prepare the ZeroMQ context and publisher socket
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);


		std::cout<<"ZMQ_VERSION "<<ZMQ_VERSION<<std::endl;
    zmq::socket_t curve_server(context, zmq::socket_type::router);
    std::cout<<"has_curve="<<zmq_has("curve")<<std::endl;
    std::cout<<"has_tls="<<zmq_has("tls")<<std::endl;


    // Bind the publisher to a TCP port
    publisher.bind("tcp://*:5555");

    int count = 0;
    while (true) {
        // Create a message
        std::string message = "Message #" + std::to_string(count);

        // Send the message
        zmq::message_t zmq_message(message.size());
        memcpy(zmq_message.data(), message.data(), message.size());
        publisher.send(zmq_message, zmq::send_flags::none);

        std::cout << "Sent: " << message << std::endl;
        ++count;

        // Wait for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
