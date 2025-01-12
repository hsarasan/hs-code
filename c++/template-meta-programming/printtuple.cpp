#include <iostream>
#include <array>
#include <string>
#include <tuple>

template <typename T, int size, int Index=0>
void printTuple(const T t){
    if constexpr (Index<size)
    {
        std::cout<<std::get<Index>(t)<<" ";
        printTuple<T,size,Index+1>(t);
    }
}

template <typename T>
constexpr void doPrint(const T t) {
    printTuple<T,std::tuple_size_v<decltype(t)> >(t);
    std::cout<<std::endl;
}

int main(){
    constexpr auto X = std::tuple{2,true,"abc"};
    doPrint(X);
    constexpr auto Y = std::tuple{5,false,"def",1.2};
    doPrint(Y);
    return 0;
}