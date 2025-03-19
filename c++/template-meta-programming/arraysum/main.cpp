#include <iostream>
#include <array>

using namespace std;

template <typename T>
auto sum(T value){
    return value;
};

template <typename T, typename... Ts>
auto sum(T value, Ts... args){
    return value + sum(args...);
};


int main(){
    cout<<sum(1,3,4,4.4,5)<<endl;
}