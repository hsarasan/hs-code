#include <iostream>
#include <variant>
#include <type_traits>
#include <algorithm>
#include <string>
#include <typeinfo>

using namespace std;

auto visitor=[](auto & value){
    using T=decay_t<decltype(value)>; 
    if constexpr (is_same_v<T,int>){
        cout<<"int"<<endl;
    }
    else if constexpr (is_same_v<T,string>){
        cout<<"string"<<endl;
    }
    else if constexpr (is_same_v<T,double>){
        cout<<"double"<<endl;
    }
    else {
        cout<<"here "<<endl;
    }
};

int main(){
    std::variant<int,double,string> v;
    v=1;
    std::visit(visitor,v);
    return 0;
}