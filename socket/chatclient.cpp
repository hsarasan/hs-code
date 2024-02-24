#include "sockclient.h"
#include <fstream>

void handleMessage(std::string_view s){
	std::cout<<s<<std::endl;
}

void finish(){
	//std::cout<<"OK bye"<<std::endl;
	exit(1);
}

int main()
{

	SC::SockClient sc("127.0.0.1",8001);
	int count=0;
	auto scThread = std::thread(&SC::SockClient::handleEvents, &sc, handleMessage, finish);
	while (true){
		std::string msg;
		std::cout<<"Enter message to broadcast: ";
		std::getline(std::cin, msg);
		sc.sendMessage(msg);
	}
}
