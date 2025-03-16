#include <iostream>

using namespace std;

template <int N>
struct factorial{
    static constexpr int value=N*factorial<N-1>::value;
};

template<>
struct factorial<0>{
    static constexpr int value=1;
};

int main(){
    cout<<factorial<5>::value<<endl;
    return 0;
}