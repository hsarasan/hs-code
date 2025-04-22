#include <iostream>

using namespace std;

template <typename T>
T sum(T value){
    return value;
}

template <typename T, typename... Ts>
auto sum(T a, Ts... args){
    return a+sum(args...);
}

int main(){
    cout<<sum(2.1,3,5.2,12);
    return 0;
}