#include <iostream>

using namespace std;

template <int N, int divisor>
struct checkDivisibilityTill2{
    constexpr static bool value=(N%divisor!=0) && checkDivisibilityTill2<N,divisor-1>::value;
};

template <int N>
struct checkDivisibilityTill2<N,2>{
    constexpr static bool value=(N%2==1);
};

template <int N>
struct checkDivisibilityTill2<N,1>{
    constexpr static bool value=(N%2==1);
};

template <int N>
struct checkDivisibilityTill2<N,0>{
    constexpr static bool value=(N%2==1);
};

template <int N>
struct is_Prime{
    constexpr static bool value=(N>2) && checkDivisibilityTill2<N,N/2>::value;
};

template <int N>
constexpr static bool is_Prime_v=is_Prime<N>::value;

int main(){
    cout<<is_Prime_v<1><<endl;
    cout<<is_Prime_v<2><<endl;
    cout<<is_Prime_v<3><<endl;
    cout<<is_Prime_v<4><<endl;
    cout<<is_Prime_v<5><<endl;
    cout<<is_Prime_v<6><<endl;
    cout<<is_Prime_v<7><<endl;
    return 0;
}