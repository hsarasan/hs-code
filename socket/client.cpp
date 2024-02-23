#include "sockclient.h"

int main()
{

	SC::SockClient sc("127.0.0.1",8001);
  sc.sendAndReceive();
}
