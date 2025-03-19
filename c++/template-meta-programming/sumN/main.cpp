#include <iostream>

using namespace std;

template <int N, int First, int... Nums>
struct sumN{
    constexpr static int value=First+sumN<N-1,Nums...>::value;
};

template <int First, int... Nums>
struct sumN<0,First,Nums...>{
    constexpr static int value=0;
};

template <int N, int First, int... Nums>
constexpr static int sumN_v=sumN<N,First,Nums...>::value;

int main(){
    cout<<sumN_v<3,1,2,3,4,5><<endl;
    return 0;
}