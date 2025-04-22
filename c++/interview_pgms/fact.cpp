#include <iostream>

using namespace std;



template <int N>
struct fact{
    constexpr static int value=N*fact<N-1>::value;
};

template <>
struct fact<0>{
    constexpr static int value=1;
};

template <int N>
constexpr static int fact_v=fact<N>::value;

int main(){

    cout<<fact_v<5><<endl;
}