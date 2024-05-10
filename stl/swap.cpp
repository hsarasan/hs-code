#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>

int main(){
    std::vector<int> v{1,2,3,4,5};
    auto it = std::find(v.begin(), v.end(), 3);
    std::cout<<*it<<std::endl;
    std::vector<int> v2{10,20,30};
    v.swap(v2);
    std::cout<<*it<<std::endl;
    std::cout<<v.size()<<" "<<v2.size()<<std::endl;
}

