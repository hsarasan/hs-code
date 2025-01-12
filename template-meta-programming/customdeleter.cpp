#include <iostream>
#include <memory>

using namespace std;

struct X{
    X(){ cout<<"Creating the object "<<endl;}
    ~X(){cout<<"Deleting the object "<<this<<endl;}
};

auto deleter=[](auto p){
    cout<<"Going to delete "<<p<<endl;
    ::delete p;
};

int main(){
    shared_ptr<X> x(new X,deleter);
    return 0;
}