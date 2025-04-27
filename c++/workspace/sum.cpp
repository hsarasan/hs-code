#include <iostream>

using namespace std;

template <typename T>
auto sum(T value){
    return value;
}

template <typename T, typename... Args>
auto sum(T value, Args... args){
    return value + sum(args...);
}

int main(){
    cout<<sum(1,2.4,31.23,true);
}