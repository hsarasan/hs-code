#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <variant>
#include <type_traits>
#include <ranges>

int main(){
    using mixed=std::variant<int,std::string,double> ;
    std::vector<mixed> v{1,"abc",1.2,4,6,"def"};
    std::ranges::sort(v);
    auto printer=[&](const auto &v){
        if (std::is_same_v< std::decay_t<decltype(v)>,  int> ){
            std::cout<<"i"<<v<<std::endl;
        }
        else if (std::is_same_v< std::decay_t<decltype(v)>,  std::string> ){
            std::cout<<"s"<<v<<std::endl;
        }
        else if (std::is_same_v< std::decay_t<decltype(v)>,  double> ){
            std::cout<<"d"<<v<<std::endl;
        }
        else {
            std::cout<<"WTF"<<std::endl;
        }
    };
    for ( const auto & w:v){
        std::visit(printer, w);
    }
}