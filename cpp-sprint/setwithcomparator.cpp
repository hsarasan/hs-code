/*
    set with a custom comparator
*/

#include <iostream>
#include <set>

struct comparator{
    bool operator()(const int &x, const int &y) const{
        return  x > y;
    }
};


int main(){
    std::set<int> S1{-3,-2,-1,0,1,2,3,4};
    std::set<int, comparator> S2{-3,-2,-1,0,1,2,3,4};
    for (const auto &  k : S2)
        std::cout<<k<<" ";
}