#include "sockserver.h"


int main() {

	std::thread sockThread(socketInit,8001);
  sockThread.join();
	return 0;
}

