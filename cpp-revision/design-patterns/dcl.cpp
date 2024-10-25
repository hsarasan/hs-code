#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>

using namespace std;

class Singleton{
    Singleton()=default;
    static Singleton * instance;
    static mutex m;
    Singleton(const Singleton &)=delete;
    Singleton & operator=(const Singleton &)=delete;
    public:
        static Singleton & createInstance(){
            if (instance==nullptr){
                lock_guard<mutex> lg(m);
                instance = new Singleton();
            }
            return *instance;
        }
        void show(){
            cout<<this<<endl;
        }
};

Singleton * Singleton::instance;
mutex Singleton::m;

int main(){
    Singleton::createInstance().show();
    Singleton::createInstance().show();
    return 0;
}