#include <iostream>
#include <type_traits>
#include <cassert>

using namespace std;


template <typename T, typename = void> struct if_foo_exists : false_type {};

template <typename T>
struct if_foo_exists<T, std::void_t<decltype(std::declval<T>().foo())>> : std::true_type {};

struct WithFoo{
    void foo(){}
};

struct WithOutFoo{};

int main(){
    static_assert(!if_foo_exists<WithOutFoo>::value);
    static_assert(if_foo_exists<WithFoo>::value);
    using T  = std::void_t<void>;
    return 0;
}