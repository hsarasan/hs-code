#include "sockserver.h"
#include "eventhandler.h"


int main() {

	int fd = socketInit(8001);
  std::cout<<"FD = "<<fd<<std::endl;
  EV::ServerSocketHandler ev;
  std::thread evHandler(&EV::ServerSocketHandler::handleEvents,&ev,fd);
	evHandler.join();
	return 0;
}

