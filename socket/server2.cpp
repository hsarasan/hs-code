#include "sockserver.h"
#include <chrono>
#include <thread>


std::string callback(std::string message){

	static int value;
	std::cout<<"Received from client "<<message<<std::endl;
	return "message from server " + std::to_string(++value);

}


int main() {

  EV::ServerSocketHandler ev;
  std::thread evHandler(&EV::ServerSocketHandler::listenAndCallback,&ev,8001, callback);
	while(1) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	evHandler.join();
	return 0;
}

