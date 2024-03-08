#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include <iterator>

template <int size=3>
class LRU{

        std::list<int> List;
        void evictLRU(){
            List.pop_back();
        }
    public:
        void printCache(){
            std::copy(List.begin(), List.end(), std::ostream_iterator<int> (std::cout,","));
            std::cout<<std::endl;
        }
        void add(const int key){
            if(List.size()>=size){
                evictLRU();
            }
            List.push_front(key);
        }
        void remove(const int key){
            List.erase(std::remove(List.begin(), List.end(), key),List.end());
        }
        int get(const int key){
            auto iter = std::find(List.begin(), List.end(), key);
            int ret = iter==List.end()?-1:key;
            List.splice(List.begin(),List,iter);
            return ret;
        }
};


int main(){

    LRU lru;
    lru.add(1);
    lru.add(2);
    lru.add(3);
    lru.printCache();
    lru.add(4);
    int x = lru.get(2);
    x  = lru.get(3);
    lru.add(5);
    lru.remove(3);
    lru.printCache();
    lru.get(6);
    lru.printCache();
    lru.add(6);
    lru.add(7);
    x=lru.get(5);
    lru.printCache();
}