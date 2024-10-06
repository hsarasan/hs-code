#include <bits/stdc++.h>

using namespace std;


class Interface{
    public:
        virtual void doSomething()=0;
};
class Task{
    Interface * pImpl;
    public:
        Task(Interface * impl):pImpl(impl){}
        void doSomething(){
            pImpl->doSomething();
        }
};
class Implementation:public Interface{
    public:
        void doSomething(){cout<<"Doing something "<<endl;}
};
int main(){
    Implementation myImpl;
    Task ts(&myImpl);
    ts.doSomething();
    return 0;
}