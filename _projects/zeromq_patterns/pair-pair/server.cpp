#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

void server_side( zmq::socket_t & socket){
		while(true){
    	zmq::message_t request;
    	socket.recv(request, zmq::recv_flags::none);
    	std::string msg(static_cast<char*>(request.data()), request.size());

    	std::cout << "[SERVER] Received: " << msg << std::endl;

    	// Send response back
    	std::this_thread::sleep_for(std::chrono::seconds(1));
    	std::string reply = "Reply from Server";
    	socket.send(zmq::message_t(reply), zmq::send_flags::none);
    	std::cout << "[SERVER] Sent reply\n";
		}
}

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.bind("tcp://*:5555");
    std::cout << "P2P Server started...\n";

		std::thread tid(server_side, std::ref(socket));
		tid.join();

    return 0;
}

