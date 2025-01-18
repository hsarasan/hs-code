#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <random>
#include "message.pb.h"

int main() {
    // Initialize the ZeroMQ context
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.bind("tcp://*:5555");


    while (true) {

    	Data data;
    	data.set_name("Temperature");
			int temp=40+std::rand()%4;
    	data.set_value(temp);
    	std::cout << "Sending message: " << data.name() << " = " << data.value() << std::endl;
    	std::string serialized_data;
    	data.SerializeToString(&serialized_data);
      socket.send(zmq::buffer(serialized_data), zmq::send_flags::none);
      std::this_thread::sleep_for(std::chrono::seconds(1));  // Send every second

    }

    return 0;
}
