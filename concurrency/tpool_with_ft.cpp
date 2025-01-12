#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <future>
#include <functional>
#include <atomic>

std::queue<std::packaged_task<int()> > Q;
std::condition_variable cv;
std::mutex mx;
std::atomic<bool> done{false};
class threadpool{
    std::vector<std::thread> threads;
    public:
        threadpool(){
            for (int i=0;i<10;++i){
                threads.emplace_back(threadpool::do_work,this);
            }
        }
        void do_work(){

            while(true){
                std::unique_lock<std::mutex> lk(mx);
                auto ready=[&](){ return !Q.empty() || done.load()==true;};
                cv.wait(lk,ready);
                if (done.load()==true) break;
                auto task=std::move(Q.front());
                Q.pop();
                task();
            }    
            std::cout<<"Thread exiting..."<<std::endl;
        }
        void stop(){
            done.store(true);
            cv.notify_all();
            std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
        }
        auto submit(std::function<int ()> f){
            std::packaged_task<int()> pt(f);
            auto fut=pt.get_future();
            auto sh_fut=fut.share();
            Q.push(std::move(pt));
            cv.notify_one();
            return sh_fut;
        }
};

int f(){
    static int x;
    std::cout<<"Executing f"<<std::endl;
    return x++*x++;
}
int g(){
    static int x=1;
    std::cout<<"Executing g"<<std::endl;
    return 10*x++;;
}
int main(){
    threadpool tp;
    for (int i=1;i<10;++i){
        auto result=tp.submit(f);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        auto result2=tp.submit(g);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout<<result.get()<<" "<<result2.get()<<std::endl;
    }
    tp.stop();
    return 0;
}