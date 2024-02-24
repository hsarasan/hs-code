#include "sockserver.h"
#include <chrono>
#include <thread>


EV::ServerSocketHandler ev;
std::string callback(std::string message, int fd){

	static int value;
	//std::cout<<"Received from client "<<message<<std::endl;
	ev.broadcast(message,fd);
	return "";
	//return "message broadcasted " + std::to_string(++value);

}


int main() {


  std::thread evHandler(&EV::ServerSocketHandler::listenAndCallback,&ev,8001, callback);
	while(1) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	evHandler.join();
	return 0;
}

