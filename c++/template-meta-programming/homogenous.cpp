#include <iostream>
#include <array>
#include <string>
#include <tuple>

template <typename T, typename... Args>
constexpr bool isHomogenous(T t, Args... args){
    return (std::is_same_v<T,Args> && ...);
}


int main(){
    std::cout<<isHomogenous(1,2.4)<<std::endl;
    std::cout<<isHomogenous(1,2,4)<<std::endl;
    std::cout<<isHomogenous(1,"abc")<<std::endl;
}