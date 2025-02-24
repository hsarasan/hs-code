#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t puller(context, zmq::socket_type::pull);
    puller.connect("tcp://localhost:5555");

    std::cout << "[WORKER] Waiting for tasks...\n";

    while (true) {
        zmq::message_t task;
        puller.recv(task, zmq::recv_flags::none);
        std::string task_str(static_cast<char*>(task.data()), task.size());

        std::cout << "[WORKER] Received: " << task_str << std::endl;

        // Simulate processing
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
