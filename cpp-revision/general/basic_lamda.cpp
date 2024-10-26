#include <iostream>
#include <memory>
#include <type_traits>

using namespace std;

struct X{};


int main(){
    int i(10);
    auto f1=[&](int j){ cout<<i+j<<endl; i=20;};
    cout<<i<<endl;
    f1(20);
    cout<<i<<endl;
    auto f2=[=]() mutable { i=25; cout<<i<<endl; };
    f2();
    cout<<i<<endl;
    return 0;
}