#include <iostream>
#include <concepts>

using namespace std;

template <typename T>
concept Addable=requires(T a, T b){
    {a+b}->std::same_as<T>;
};

template <Addable T>
T add(T a, T b){
    return a+b;
}

int main(){
    cout<<add(3,4)<<endl;
    //cout<<add("abc","def")<<endl;
    cout<<add(string("abc"),string("def"))<<endl;
    return 0;
}