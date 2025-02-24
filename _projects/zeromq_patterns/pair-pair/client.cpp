#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

void sender(zmq::socket_t &socket){

	while(true){
        std::string message = "Hello from Client";
        socket.send(zmq::message_t(message), zmq::send_flags::none);
        std::cout << "[CLIENT] Sent: " << message << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}
void receiver(zmq::socket_t &socket){
	while(true){
        // Receive response
        zmq::message_t reply;
        socket.recv(reply, zmq::recv_flags::none);
        std::cout << "[CLIENT] Received: " << std::string(static_cast<char*>(reply.data()), reply.size()) << std::endl;
	}
}

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.connect("tcp://localhost:5555");

		std::thread send_thr(sender,std::ref(socket));
		std::thread recv_thr(receiver,std::ref(socket));
		send_thr.join();
		recv_thr.join();

    return 0;
}

