#include <iostream>
#include <type_traits>

using namespace std;

template <typename T, typename... Ts>
struct Tuple{
    Tuple(T value_, Ts... args):value(value_),rest(args...){}
    T value;
    Tuple<Ts...> rest;
};
template <typename T>
struct Tuple<T>{
    Tuple(T value_):value(value_){}
    T value;
};


template <int N>
struct getter{
    template <typename... Ts> 
    static auto get(Tuple<Ts...> & tup){
        return getter<N-1>::get(tup.rest);
    }
};
template <>
struct getter<0>{
    template <typename T, typename... Ts> 
    static T get(Tuple<T,Ts...> & tup){
        return tup.value;
    }
};

template <int N, typename... Ts>
auto get(Tuple<Ts...> arg){
    return getter<N>::get(arg);
}

int main(){
    Tuple<int,char,int> var(1,'c',9);
    cout<<get<0>(var)<<endl;
    cout<<get<1>(var)<<endl;
    cout<<get<2>(var)<<endl;
    return 0;
}