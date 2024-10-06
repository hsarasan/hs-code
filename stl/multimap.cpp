#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <queue>

using namespace std;

int main(){
    unordered_multimap<int,string> hash_map;
    hash_map.insert({0,"zero"});
    hash_map.insert({0,"Zero"});
    hash_map.insert({1,"one"});
    hash_map.insert({1,"One"});
    hash_map.insert({2,"two"});
    hash_map.insert({3,"three"});
    auto range=hash_map.equal_range(1);
    auto iter = range.first;
    while (iter!=range.second){
        cout<<iter->second<<endl;
        iter=++iter;
    }
}


