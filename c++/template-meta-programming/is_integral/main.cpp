#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
struct is_Integral:std::false_type{};

template <> 
struct is_Integral<int> :std::true_type{};


int main(){

    cout<<is_Integral<int>::value<<endl;
    cout<<is_Integral<char*>::value<<endl;

}