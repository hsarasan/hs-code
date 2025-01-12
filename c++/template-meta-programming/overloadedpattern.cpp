#include <string>
#include <iostream>
#include <variant>
#include <algorithm>
#include <type_traits>
#include <vector>

template<typename... Ts>                                                 // (7) 
struct Overload : Ts ... { 
    using Ts::operator() ...;
};


int main() {

    using vartype=std::variant<int,std::string,bool>;
    std::vector<vartype> v{1,"abcd",3,true};

    auto overloaded_lamdas= Overload{
        [](int v){ std::cout<<"Integer "<<v<<std::endl;},
        [](bool v){ std::cout<<"bool "<<v<<std::endl;},
        [](std::string v){ std::cout<<"string "<<v<<std::endl;}
    };
    for (auto  val: v){
        std::visit(overloaded_lamdas,val);
    }
    return 0;
}