#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

using Func=std::function<void()>;


class ThreadPool{

    public:
        ThreadPool(){
            for (int i=0;i<5;++i)
                threads.emplace_back(ThreadPool::execute,this);
        }
        void submit(Func f){
            {
                lock_guard<mutex> lg(mx);
                Q.push(f);
            }
            cv.notify_one();
        }
        void shutdown(){
            if (stop) return;
            {   
                lock_guard<mutex> lg(mx);
                stop=true;
            }
            cv.notify_all();
            for (auto & t: threads)
                t.join();
        }
        ~ThreadPool(){
            shutdown();
        }
    private:
        void execute(){
            Func task;
            while (true){
                {
                unique_lock<mutex> ul(mx);
                    cv.wait(ul,[&](){return stop||!Q.empty();});
                    if (!Q.empty()){
                        task=Q.front();
                        Q.pop();
                    }
                    else{
                        if (stop) break;
                    }
                }
                task();
            }
        }
    vector<thread> threads;
    mutex mx;
    condition_variable cv;
    bool stop{false};
    queue<Func> Q;
};


int main(){
    ThreadPool tp;
    auto lambda=[](){
        cout<<"Inside lambda "<<endl;
        usleep(1000000);
    };
    int i=0;
    while(i<5){
        i++;
        tp.submit(lambda);
    }
    cout<<"All done "<<endl;
    tp.shutdown();
    return 0;
}