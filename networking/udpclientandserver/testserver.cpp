#include "udpwrapper.h"

int main(int argc, char *argv[]) {

    if (argc<4) {
        std::cerr<<"Usage : "<<argv[0]<<" InstanceNumber ListenPort SendPort"<<std::endl;
        exit(1);
    }
    int instance = atoi(argv[1]);
    int listenPort = atoi(argv[2]);
    int sendPort = atoi(argv[3]);

    UDPServer udpserver(listenPort);
    udpserver.process();
    UDPClient udpclient(instance, sendPort);
    udpclient.process();
    for (;;){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        /* do other stuff*/
    }
    return 0;
}