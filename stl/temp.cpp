#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>

int main(){
    std::vector<int> v{1,2,3,4,5,7,9};
    auto it = std::lower_bound(v.begin(), v.end(), 4);
    auto it2 = std::upper_bound(v.begin(), v.end(), 4);
    std::cout<<*it<<" "<<*it2<<std::endl;
    it = std::lower_bound(v.begin(), v.end(), 6);
    it2 = std::upper_bound(v.begin(), v.end(), 6);
    std::cout<<*it<<" "<<*it2<<std::endl;
}

