#include <iostream>

using namespace std;

template <typename T, typename U>
struct isSame{
    constexpr static bool value=false;
};

template <typename T>
struct isSame<T,T>{
    constexpr static bool value=true;
};

template <typename T, typename U>
constexpr static bool isSame_v=isSame<T,U>::value;

int main(){
    cout<<isSame_v<int,int><<endl;
    cout<<isSame_v<int,char><<endl;
    return 0;
}