#include "sockserver.h"
#include <chrono>
#include <thread>
#include <unordered_map>
#include <unordered_set>


EV::ServerSocketHandler ev;
std::unordered_map<std::string, int> connectionPool;
std::unordered_set<int> fds;

std::string callback(std::string message, int fd){

	if ( message.find("login@") != std::string::npos ){
		auto username = message.substr(6,string::npos);
		if (connectionPool.count(username)==0) {
			std::cout<<"added "<<username<<std::endl;
			connectionPool[username]=fd;
			fds.insert(fd);
		}
		else{
			if (fd!=connectionPool[username]){
				std::cout<<"duplicate login "<<username<<std::endl;
				return "close";
			}
			else {
				return "";
			}
		}
	}
	else{
		if ( fds.count(fd)==0){
			return "close";
		}
		ev.broadcast(message,fd);
	}
	return "";

}


int main() {


  std::thread evHandler(&EV::ServerSocketHandler::listenAndCallback,&ev,8001, callback);
	while(1) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		//std::cout<<"Valid Connections = "<<ev.getNumberOfConnections()<<std::endl;
	}
	evHandler.join();
	return 0;
}

