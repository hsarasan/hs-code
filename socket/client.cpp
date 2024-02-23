#include "sockclient.h"

int main()
{

	SC::SockClient sc("127.0.0.1",8001);
	int count=0;
  while(count++<100){
  	sc.sendMessage(std::to_string(getpid())+ "=>" + std::to_string(count));
		std::cout<<".";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
