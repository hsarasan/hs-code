/* TMP function to find the dim of an array at compile time */
#include <iostream>

template <typename T>
struct dimofarray{
    static constexpr int value=0;
};
template <typename T, int N>
struct dimofarray<T[N]>{
    static constexpr int value=1+dimofarray<T>::value;
};

int main(){
    int x[3];
    constexpr int i=dimofarray<decltype(x)>::value;
    static_assert(i==1);
    int y[3][2];
    constexpr int j=dimofarray<decltype(y)>::value;
    static_assert(j==2);
    return 0;
}


