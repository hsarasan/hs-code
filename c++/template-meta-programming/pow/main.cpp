#include <iostream>

using namespace std;

template <int val,int exp>
struct Pow{
    constexpr static int value=val*Pow<val,exp-1>::value;
};

template <int val>
struct Pow<val,0>{
    constexpr static int value=1;
};

template <int val,int exp>
constexpr static int Pow_v=Pow<val,exp>::value;

int main(){
    cout<<Pow_v<3,2><<endl;
    return 0;
}