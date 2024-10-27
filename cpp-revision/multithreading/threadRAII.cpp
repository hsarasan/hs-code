#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <mutex>

using namespace std;
mutex m;

void thread_func(){
    lock_guard<mutex> lg(m);
    cout<<"From thread "<<this_thread::get_id()<<endl;
}

class ThreadRAII{
    thread t;
    bool join;
    public:
        ThreadRAII(thread &&t_, bool join_=true):t(move(t_)),join(join_){}
        ~ThreadRAII(){
            if (t.joinable()){
                cout<<boolalpha<<" join? "<<join<<endl;
                if (join) t.join();
                else t.detach();
                cout<<"after join "<<endl;
            }
        }
};

int main(){
    ThreadRAII thr( thread{thread_func});
    return 0;
}