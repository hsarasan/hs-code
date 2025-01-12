#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <algorithm>

using namespace std::chrono_literals;
using UserFunction = std::function<void(int i)>;
class ThreadPool{

    std::vector<std::thread> threads;
    std::queue<UserFunction> workerQ;
    std::condition_variable cv;
    std::atomic<bool> done{false};
    std::mutex cv_m, Qlock,printMutex;

    void doWork(){
        static thread_local int counter{0};
        while(!done.load())
        {
            {
                if (!workerQ.empty())
                {
                    Qlock.lock();
                    if (!workerQ.empty())
                    {
                        UserFunction execute = workerQ.front();
                        workerQ.pop();
                        Qlock.unlock();
                        static int x;
                        execute(x++);
                        counter++;
                    }
                    else{
                        Qlock.unlock();
                    }
                }
                else
                {
                    std::this_thread::sleep_for(1s);
                }
            }
        }
        std::lock_guard<std::mutex>lk(printMutex);
        std::cout<<"exiting...E"<<std::this_thread::get_id()<<" Exexcuted "<<counter<<std::endl;
    }

    public:
    ThreadPool()
    {
        
        for (int i=0;i<5;++i)
        {
            threads.emplace_back(&ThreadPool::doWork, this);
        }
    }
    void shutdown(){
        std::cout<<"Shutting down.."<<std::endl;
        done.store(true);
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    }
    ~ThreadPool()
    {
        
    }
    void submitJob(UserFunction f)
    {
        workerQ.push(f);
    }
};

std::mutex m;
void print(std::string s, int x)
{
    static int count{0};
    std::lock_guard<std::mutex> lk(m);
    std::cout<<"ThreadId["<<std::this_thread::get_id()<<"]=>"<<s<<" "<<x<<std::endl;
    std::this_thread::sleep_for(200ms);
    std::cout<<"Executed globally "<<++count<<std::endl;
}
void f(int x) {
    print("f",x);
}
void g(int x){
    print("g",x);
}

auto lamda = [](int x){     
    print("lamda",x);
};


struct X{
    
    void x(int y){    
        print("X::x()",y);
    }
};

int main(){

    ThreadPool tPool;
    int i=0;
    
    while(i<100)
    {
    tPool.submitJob(f);
    tPool.submitJob(f);
    tPool.submitJob(lamda);
    tPool.submitJob(g);
    X x;
    auto fx = std::bind(&X::x,x,0);
    tPool.submitJob(fx);
    i++;
    std::cout<<i<<std::endl;
    std::this_thread::sleep_for(200ms);
    }
    std::this_thread::sleep_for(5s);
    tPool.shutdown();
    return 0;
}