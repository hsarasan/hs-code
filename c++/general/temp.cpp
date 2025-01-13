#include <iostream>
#include <vector>

int main(){
    std::vector<int> v(10,1);
    std::cout<<v.back()<<std::endl;
    std::cout<<v.size()<<std::endl;
}