#include <iostream>
#include <type_traits>

using namespace std;

template <typename T, typename T2=void> struct does_foo_exist:std::false_type{};
template <typename T> struct does_foo_exist <T, std::void_t<decltype(declval<T>().foo())> > : true_type{};

struct WithFoo{
    void foo(){}
};

struct WithOutFoo{};

int main(){
    cout<<does_foo_exist<WithFoo>::value<<endl;
    cout<<does_foo_exist<WithOutFoo>::value<<endl;
    return 0;
}