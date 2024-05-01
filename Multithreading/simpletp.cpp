#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;
using namespace std::placeholders;
using fn=std::function<void (int)>;
bool done{false};
template <int sz=4>
class Pool{
        int count{0};
        std::queue<fn> Q;
        std::condition_variable cv;
        std::mutex m;
        std::mutex printMutex;
        std::mutex qMx;
        std::vector<std::thread> threads;

        void doWork(){
            
            while(!done){
                std::unique_lock<std::mutex> ul(m);
                cv.wait(ul,[&](){return !Q.empty() || done;});
                if(done) { 
                    std::cout<<"Thread: "<<std::this_thread::get_id()<<" exiting..."<<std::endl;
                    break;
                }
                std::unique_lock<std::mutex> ql(qMx);
                auto g1 = Q.front();
                Q.pop();
                ql.unlock();
                int dummy(0);
                g1(dummy);
                std::this_thread::sleep_for(2s);
                std::unique_lock<std::mutex> pm(printMutex);
                std::cout<<"Job: "<<std::this_thread::get_id()<<" "<<count++<<std::endl;
                pm.unlock();
            }
            std::lock_guard<std::mutex> pm(printMutex);
        }
    public:
        Pool(){
            int x=sz;
            for (int i=0;i<sz;++i)
                threads.emplace_back(std::thread(&Pool::doWork,this));
        }
        void stop(){
            cv.notify_all();
            //std::cout<<"In stop "<<std::endl;
            std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
        }
        void submitJob(fn f1, int arg){
            std::cout<<"In Submit"<<std::endl;
            auto g = std::bind(f1,arg);
            Q.push(g);
            cv.notify_one();
        }

};


void f(int count){
    static int x;
    count=count+x;
    x=count;
    std::cout<<"From f()=>"<<count<<std::endl;
    
}

auto Doubler = [](int val){
    std::cout<<"From Doubler "<<val*2<<std::endl;
};
int main(){
    Pool tp;
    int count=0;
    while(count<4){
        count++;
        tp.submitJob(f,count*100);
        tp.submitJob(Doubler,count);
        std::this_thread::sleep_for(3s);
    }
    done = true;
    tp.stop();
    std::cout<<"Bye.."<<std::endl;
}