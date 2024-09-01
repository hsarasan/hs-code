#include <iostream>
#include <vector>
#include <algorithm>

class Demo{

    public:
    int value;
    Demo(int v):value(v){ std::cout<<"Default Ctor "<<std::endl;;}
    Demo(const Demo & d){ std::cout<<"copy Ctor "<<std::endl;; value=d.value;}
    Demo(Demo && d) noexcept { std::cout<<"move Ctor "<<std::endl; value=d.value;}

};
int main(){
    std::vector<Demo> v;
    v.reserve(20);

    Demo d(1);
    std::cout<<"================"<<std::endl;
    v.push_back(d);
    std::cout<<"After PB Local value "<<std::endl;
    v.emplace_back(d);
    std::cout<<"After EB Local value "<<std::endl;
    v.emplace_back(5);
    std::cout<<"After EB implicit construction "<<std::endl;
    v.push_back(Demo(10));
    std::cout<<"After PB Temp obj"<<std::endl;
    v.emplace_back(Demo(12));
    std::cout<<"After EB Local value "<<std::endl;
}