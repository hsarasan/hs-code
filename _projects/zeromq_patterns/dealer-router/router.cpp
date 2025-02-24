#include <zmq.hpp>
#include <iostream>
#include <queue>
#include <unordered_map>

int main() {
    zmq::context_t context(1);
    zmq::socket_t router(context, zmq::socket_type::router);
    router.bind("tcp://*:5555");

    std::queue<std::string> worker_queue;
    std::unordered_map<std::string, std::string> request_map;

    std::cout << "Router ready...\n";

    while (true) {
        zmq::message_t sender_id;
        router.recv(sender_id, zmq::recv_flags::none);
        std::string sender(static_cast<char*>(sender_id.data()), sender_id.size());

        zmq::message_t msg;
        router.recv(msg, zmq::recv_flags::none);

        std::string msg_str(static_cast<char*>(msg.data()), msg.size());

        if (msg_str == "READY") {
            // Worker registration
            worker_queue.push(sender);
            std::cout << "Worker registered: " << sender << std::endl;
        } else if (request_map.count(sender)) {
            // This is a response from a worker
            zmq::message_t client_id(request_map[sender].data(), request_map[sender].size());
            router.send(client_id, zmq::send_flags::sndmore);
            router.send(msg, zmq::send_flags::none);

            request_map.erase(sender);
            worker_queue.push(sender);  // Worker is available again
            std::cout << "Worker " << sender << " response forwarded to client.\n";
        } else {
            // Incoming request from client (Dealer)
            if (!worker_queue.empty()) {
                std::string worker = worker_queue.front();
                worker_queue.pop();

                request_map[worker] = sender;

                router.send(zmq::message_t(worker), zmq::send_flags::sndmore);
                router.send(sender_id, zmq::send_flags::sndmore);
                router.send(msg, zmq::send_flags::none);

                std::cout << "Forwarded request to Worker: " << worker << std::endl;
            } else {
                std::cout << "No workers available, dropping request\n";
            }
        }
    }

    return 0;
}
