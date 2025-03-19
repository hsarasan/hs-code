#include <iostream>

using namespace std;

template <typename T>
struct isPointer{
    constexpr static bool value=false;
};
template <typename T>
struct isPointer<T*>{
    constexpr static bool value=true;
};

template <typename T>
constexpr static bool isPointer_v=isPointer<T>::value;

int main(){
    cout<<isPointer_v<char><<endl;
    cout<<isPointer_v<char*><<endl;
    return 0;
}