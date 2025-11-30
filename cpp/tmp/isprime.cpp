#include <iostream>

template <int N, int M>
struct isDivisible {
    static constexpr bool value = (N % M == 0) ? true: isDivisible<N, M-1>::value;
};

template <int N>
struct isDivisible<N, 0> {
    static constexpr bool value = false; // Division by zero case
};
template <int N>
struct isDivisible<N, 1> {
    static constexpr bool value = false; // Division by zero case
};
template <int N>
struct isPrime{
    static constexpr bool value = !isDivisible<N,N/2>::value;
};

template <>
struct isPrime<1>{
    static constexpr bool value = true;
};

template <>
struct isPrime<2>{
    static constexpr bool value = true;
};

int main() {
    std::cout << isPrime<2>::value <<std::endl;
    std::cout << isPrime<3>::value <<std::endl;
    std::cout << isPrime<4>::value <<std::endl;
    std::cout << isPrime<5>::value <<std::endl;
    std::cout << isPrime<6>::value <<std::endl;

    return 0;
}