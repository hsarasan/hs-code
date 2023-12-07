/*
Implement the RandomizedSet class:

RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in average O(1) time complexity.

*/

#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdlib>

class RandomizedSet {

    std::unordered_map<int, int> map;
    std::vector<int> v;
public:
    RandomizedSet() {
        
    }

    void print() {
        std::cout<<"MAP"<<std::endl;
        for (const auto & [k,v] : map)
        {
            std::cout<<k<<"=>"<<v<<std::endl;
        }
        std::cout<<"Vector"<<std::endl;
        for (const auto & i : v)
        {
            std::cout<<i<<" ";
        }
        std::cout<<std::endl;
    }
    
    bool insert(int val) {
        if (map.count(val)) return false;
        v.emplace_back(val);
        map[val]=v.size()-1;

        return true;
    }
    
    bool remove(int val) {
        
        if (!map.count(val)) return false;
        int vIndex = map[val];
    
        int back_val = v.back();
        v[vIndex] = back_val;
        map[back_val] = vIndex;
        v.pop_back();
        map.erase(val);
        return true;
    }
    
    int getRandom() {
        int idx = std::rand()%v.size();
        return v[idx];
    }
};

int main(){

    RandomizedSet r;
    bool b ;
    b = r.insert(0);
    r.print();
    b  = r.insert(1);
    r.print();
    b = r.remove(0);
    r.print();
    b = r.insert(2);
    r.print();
    b = r.remove(1);
    r.print();
    int i = r.getRandom();
    std::cout<<i<<std::endl;



}
