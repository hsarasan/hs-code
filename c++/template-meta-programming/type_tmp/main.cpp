#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
struct remove_extents{
    using Type=T;
};
template <typename T, size_t N>
struct remove_extents<T[N]>{
    using Type=T;
};

template <typename T>
struct remove_extents<T[]> {
    using Type = T;
};

int main(){
    using INT=remove_extents<int[]>::Type;
    using INT2=remove_extents<int[2]>::Type;
    cout<<is_same_v<int,INT><<endl;
    cout<<is_same_v<int,INT2><<endl;
    return 0;
}