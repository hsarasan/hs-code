#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>

int get_val(){
    return std::rand();
}

int main(){
    int max_v=2000;
    int min_v=1000;
    for (int i=0;i<100;++i)
        std::cout<<std::clamp(get_val(), min_v, max_v)<<std::endl;

}