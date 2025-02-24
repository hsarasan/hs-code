#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t worker(context, zmq::socket_type::dealer);
    worker.connect("tcp://localhost:5555");

    // Send "READY" as a proper message
    worker.send(zmq::message_t("READY", 5), zmq::send_flags::none);
    std::cout << "Worker registered...\n";

    while (true) {
        zmq::message_t router_id, client_id, request;
        //worker.recv(router_id, zmq::recv_flags::none);
        worker.recv(client_id, zmq::recv_flags::none);
        worker.recv(request, zmq::recv_flags::none);

        std::string msg(static_cast<char*>(request.data()), request.size());
        std::cout << "Worker received request: " << msg << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Send reply back to the router
        worker.send(zmq::message_t("Processed: " + msg), zmq::send_flags::none);
        std::cout << "Worker sent response\n";
    		worker.send(zmq::message_t("READY", 5), zmq::send_flags::none);
    		std::cout << "Worker registered again...\n";
    }

    return 0;
}

