#include <iostream>


template <unsigned N>
struct Factorial{
    constexpr static unsigned value=N*Factorial<N-1>::value; 
};
template <>
struct Factorial<1>{
    constexpr static unsigned value=1;
};



int main(){
    constexpr int V = Factorial<5>::value;
    std::cout<<V<<std::endl;
    return 0;
}