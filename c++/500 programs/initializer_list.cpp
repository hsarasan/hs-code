#include <iostream>
#include <cstddef>  // for size_t

template <typename T, size_t N>
struct init_list {
    T data[N];

    // Variadic template constructor
    template <typename... U>
    init_list(U... args) : data{ static_cast<T>(args)... } {
        static_assert(sizeof...(args) == N, "Wrong number of elements");
    }

    T* begin() { return data; }
    T* end()   { return data + N; }

    const T* begin() const { return data; }
    const T* end()   const { return data + N; }
};

int main() {
    init_list<int, 4> il{1, 2, 3, 4};

    for (auto x : il)
        std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}
