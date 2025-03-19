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

int main(){
    cout<<is_Prime<1>::value<<endl;
    cout<<is_Prime<2>::value<<endl;
    cout<<is_Prime<3>::value<<endl;
    cout<<is_Prime<4>::value<<endl;
    cout<<is_Prime<5>::value<<endl;
    cout<<is_Prime<6>::value<<endl;
    cout<<is_Prime<7>::value<<endl;
    return 0;
}