#include <iostream>

using namespace std;

template <int Sqr, int N>
constexpr auto checkSqrFrom2(){
    if constexpr (Sqr*Sqr==N)
        return Sqr;
    else    
        return checkSqrFrom2<Sqr+1,N>();
}

template <int N>
struct ct_sqrt{
    constexpr static int value=checkSqrFrom2<1,N>();
};

template <int N>
constexpr static int ct_sqrt_v=ct_sqrt<N>::value;


int main(){
    int x = ct_sqrt_v<25>;
    cout<<x<<endl;
    return 0;
}