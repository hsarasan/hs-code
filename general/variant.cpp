#include <iostream>
#include <variant>
#include <vector>

void f(std::string s)
{
    std::cout<<"string "<<s<<std::endl;
}

void f(double s)
{
    std::cout<<"double "<<s<<std::endl;
}

void f(int s)
{
    std::cout<<"int "<<s<<std::endl;
}
int main() 
{
    std::vector<std::variant <int,double,std::string>> v{1,2.5};

    for (auto &var : v)
    {
        std::visit( [](auto &&arg ){ f(arg);}, var);
    }

    return 0;
}