#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

template <typename T, typename... Ts>
struct myTuple{
    T value;
    myTuple<Ts...> rest;
    myTuple(T arg, Ts... args): value(arg), rest(args...){}
    constexpr static int size = 1 + sizeof...(Ts);
    
};
template <typename T>
struct myTuple<T>{
    T value;
    myTuple(T arg): value(arg){}
    constexpr static int size = 1 ;
    
};

int main(){
    myTuple<int,string,double,char> m(1,"abc",2.4,'c');
    constexpr int sz = m.size;
    cout<<"Sz = "<<m.size<<endl;
    myTuple<int> m2(1);
    constexpr int sz2 = m2.size;
    cout<<"Sz = "<<m2.size<<endl;
}