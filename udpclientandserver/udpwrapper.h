#include "udpmessage.h"


class UDPClient
{
    int port;
    int id;
    void worker(int id, int portno)
    {
        UDP udp;
        udp.initClient(portno);
        int seqNo{0};
        for (;;){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //std::cout << "From worker thread" << std::endl;

            std::string seqMessage(std::string("SeqMessage:[")+ std::to_string(id)+"]:"+ std::to_string(seqNo++));
            udp.send(seqMessage);
        }
    }

public:
    UDPClient(int id, int portno) : port(portno),id(id) {}

    void process()
    {
        std::thread workerThread = std::thread(&UDPClient::worker, this, id, port);
        workerThread.detach();
    }
};

void callback_fn(std::string mesg){
    std::cout<<"From Select ["<<mesg<<"]"<<std::endl;
}
class UDPServer
{
    int port;
    void worker(int portno)
    {
        UDP udp;
        udp.initServer(portno);
        int seqNo{0};
        udp.setCallbackOnReceive(callback_fn);
    }

public:
    UDPServer(int portno) : port(portno) {}

    void process()
    {
        std::thread workerThread = std::thread(&UDPServer::worker, this, port);
        workerThread.detach();
    }
};