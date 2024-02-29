#include "udpmessage.h"
#include <condition_variable>
#include <mutex>
#include <atomic>

std::condition_variable cv;
std::mutex m;
std::string Message;

class UDPClient
{
    int port;
    int id;
    void worker(int id, int portno)
    {
        UDP udp;
        udp.initClient(portno);
        int seqNo{0};
        std::string seqMessage;
        for (;;)
        {
            if (id != 1)
            {
                std::unique_lock<std::mutex> lk(m);
                cv.wait(lk, []()
                        { return !Message.empty(); });
                std::cout << "From non master sending=>" << Message << std::endl;
                seqMessage = Message;
                Message.clear();
                udp.send(seqMessage);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                seqMessage = std::to_string(seqNo++);
                std::cout << "From master sending=>" << seqMessage << std::endl;
                udp.send(seqMessage);
            }
        }
    }

public:
    UDPClient(int id, int portno) : port(portno), id(id) {}

    void process()
    {
        std::thread workerThread = std::thread(&UDPClient::worker, this, id, port);
        workerThread.detach();
    }
};

void callback_fn(std::string mesg)
{
    Message = mesg;
    cv.notify_one();
}
class UDPServer
{
    int port;
    void worker(int portno)
    {
        UDP udp;
        udp.initServer(portno);
        int seqNo{0};
        udp.setCallbackOnReceive(callback_fn,3);
    }

public:
    UDPServer(int portno) : port(portno) {}

    void process()
    {
        std::thread workerThread = std::thread(&UDPServer::worker, this, port);
        workerThread.detach();
    }
};
