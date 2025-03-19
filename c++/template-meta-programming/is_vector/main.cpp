#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct isVector{
    constexpr static bool value=false;
};
template <typename T>
struct isVector<vector<T>>{
    constexpr static bool value=true;
};
template <typename T>
constexpr static bool isVector_v=isVector<T>::value;

int main(){
    cout<<isVector_v<int><<endl;
    cout<<isVector_v<vector<int>><<endl;
}