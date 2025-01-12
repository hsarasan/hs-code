#include <iostream>
#include <cassert>
#include <type_traits>

template <typename T, typename U>
struct isSame:public std::false_type{};

template <typename T>
struct isSame<T,T>:public std::true_type{};

int main(){
    int i;
    float f;
    constexpr bool b = isSame<int,decltype(i)>::value;
    static_assert(b);
    static_assert(isSame<float, decltype(f)>::value);
    static_assert(isSame<decltype(i), decltype(f)>::value);
    return 0;
}