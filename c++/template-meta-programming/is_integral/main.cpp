#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
struct is_Integral:std::false_type{};

template <> 
struct is_Integral<int> :std::true_type{};

template <typename T>
constexpr static int is_Integral_v=is_Integral<T>::value;

int main(){

    cout<<is_Integral_v<int><<endl;
    cout<<is_Integral_v<char*><<endl;

}