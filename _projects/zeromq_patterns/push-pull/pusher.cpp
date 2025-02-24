#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t pusher(context, zmq::socket_type::push);
    pusher.bind("tcp://*:5555");

    std::cout << "[PUSHER] Sending tasks...\n";

    for (int i = 0; i < 10; ++i) {
        std::string task = "Task #" + std::to_string(i);
        pusher.send(zmq::message_t(task), zmq::send_flags::none);
        std::cout << "[PUSHER] Sent: " << task << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
    }

    return 0;
}

