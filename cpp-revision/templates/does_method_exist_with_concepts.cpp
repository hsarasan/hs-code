#include <iostream>
#include <type_traits>
#include <cassert>

using namespace std;

template <typename T>
concept with_foo_struct=requires(T t){
    t.foo();
};

struct WithOutFoo{};
struct WithFoo{ void foo(){} };


int main(){
    static_assert( with_foo_struct<WithFoo>);
    static_assert( !with_foo_struct<WithOutFoo>);
    return 0;
}