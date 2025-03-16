#include <iostream>

using namespace std;

// Recursive ntuple definition
template <typename T, typename... Ts>
struct ntuple {
    T value;
    ntuple<Ts...> rest;

    // Size function
    constexpr int size() { return 1 + rest.size(); }

    // Constructor
    ntuple(T v, Ts... args) : value(v), rest(args...) {}
};

// Base case for single element
template <typename T>
struct ntuple<T> {
    T value;

    // Constructor
    ntuple(T v) : value(v) {}

    // Base case for size()
    constexpr int size() { return 1; }
};

// Recursive getter
template <size_t N>
struct getter {
    template <typename T, typename... Ts>
    static auto get(const ntuple<T, Ts...>& t) {
        return getter<N - 1>::get(t.rest);
    }
};

// Base case for getter<0>
template <>
struct getter<0> {
    template <typename T, typename... Ts>
    static auto get(const ntuple<T, Ts...>& t) {
        return t.value;
    }
};

// Wrapper function for `get<N>()`
template <size_t N, typename... Ts>
auto get(const ntuple<Ts...>& t) {
    return getter<N>::get(t);
}

int main() {
    ntuple<int, char, float> nt(1, 'a', 1.2);
    
    // Print values manually
    cout << nt.value << " " << nt.rest.value << " " << nt.rest.rest.value << endl;
    
    // Print size
    cout << "Size: " << nt.size() << endl;

    // Use `get<N>` function
    cout << "get<0>(nt): " << get<0>(nt) << endl;  // Should print 1
    cout << "get<1>(nt): " << get<1>(nt) << endl;  // Should print 'a'
    cout << "get<2>(nt): " << get<2>(nt) << endl;  // Should print 1.2

    return 0;
}
