#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

template <typename T>
T minc(T arg1, T arg2){

    return arg1<arg2?arg1:arg2;

}

template <typename T, typename... Ts>
T minc(T arg, Ts... args){

    T min_args = minc(args...);
    return arg<min_args?arg:min_args;
}

int main(){
    cout<<minc(7,4,3,2)<<endl;
    cout<<minc(string("def"),string("abc"),string("jki"))<<endl;
}
