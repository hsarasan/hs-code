#include <iostream>
#include <array>
#include <type_traits>

using namespace std;

template <typename T, size_t rows, size_t cols>
constexpr pair<size_t,size_t> getDimensions(const std::array< std::array<T,cols> , rows> &arr){
    return {rows,cols};
}

template <typename T, size_t rows, size_t cols>
constexpr auto transpose(const std::array< std::array<T,cols> , rows> &arr){
    
    std::array< std::array<T,rows>, cols> arr2{};
    for (int i=0;i<rows;++i)
    for (int j=0;j<cols;++j)
        arr2[j][i]=arr[i][j];
    return arr2;
}

int main(){
    constexpr std::array< std::array<int,3>,2> arr{{ {1,2,3}, {4,5,6}}};
    constexpr auto arr2 = transpose(arr);
    constexpr auto dim = getDimensions(arr2);
    static_assert(dim.first==3);
    static_assert(dim.second==2);
    static_assert(arr2[1][0]==2);
    static_assert(std::is_same_v< std::array< std::array<int,2>,3>, decay_t<decltype(arr2)>>);
    return 0;
}