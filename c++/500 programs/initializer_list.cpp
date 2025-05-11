#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <type_traits>

using namespace std;

template <typename T, size_t N>
struct init_list {
    T values[N];

    init_list(std::same_as<T> auto... args) 
    requires (sizeof...(args) == N)
    : values{args...} {}

    T* begin() { return values; }
    T* end()   { return values + N; }

    const T* begin() const { return values; }
    const T* end()   const { return values + N; }

};

int main() {
    init_list<int, 5> l(1, 2, 3, 4, 5);  // OK

    for (const auto & i: l){
        cout<<i<<endl;
    }

    return 0;
}
