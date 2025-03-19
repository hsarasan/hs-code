#include <iostream>

using namespace std;


template <typename T, typename... Args>
struct my_tuple_size{
    constexpr static size_t value = 1 + my_tuple_size<Args...>::value;
};

template <typename T>
struct my_tuple_size<T>{
    constexpr static size_t value=1;
};


int main(){

    constexpr size_t size = my_tuple_size<int,char,short>::value;
    std::cout << "Tuple size: " << size << std::endl;  // Output: 4
    return 0;
}