#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>

int main(){
    std::forward_list<int> f_list(20,0);
    std::iota(f_list.begin(), f_list.end(), 1);
    std::copy(f_list.begin(), f_list.end(), std::ostream_iterator<int> (std::cout,","));
    
}

