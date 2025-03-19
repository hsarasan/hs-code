#include <iostream>

using namespace std;

template <int M, int N>
struct GCD{
    constexpr static int value=GCD<N,M%N>::value;
};

template <int M>
struct GCD<M,0>{
    constexpr static int value=M;
};

template<int M, int N>
constexpr static int GCD_v=GCD<M,N>::value;

int main(){
    cout<<GCD_v<48,18><<endl;
    return 0;
}