#include <iostream>
#include <string>

using namespace std;

template <typename T, typename U>
concept Addable=requires (T a, U b){
    {a+b};
};

template <typename T, typename U>
auto add(T a, U b){
    return a+b;
}

int main(){
    cout<<add(2.4,2)<<endl;
    cout<<add(string("abc"),'d')<<endl;
    return 0;
}