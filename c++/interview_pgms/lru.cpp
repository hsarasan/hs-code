#include <iostream>
#include <unordered_map>
#include <iterator>
#include <list>

using namespace std;

template <int capacity>
struct LRUCache{
    void move_front(int key){
        auto iter=key_iter[key];
        cache.splice(cache.begin(), cache, iter);
    }
    void put(int key,int value){
        if (key_iter.count(key)>0){
            auto iter=key_iter[key];
            iter->second=value;
            move_front(key);
            return ;
        }
        cache.insert(cache.begin(), {key,value});
        key_iter[key]=cache.begin();
        if (cache.size()>capacity){
            auto iter=cache.back();
            int key_to_erase=iter.first;
            key_iter.erase(key_to_erase);
            cache.pop_back();
        }
    }
    int get(int key){
        if (key_iter.count(key)==0) return -1;
        move_front(key);
        auto iter=key_iter[key];
        return iter->second;
    }
    void print(){
        for (const auto & [key,val]:cache){
            cout<<key<<" : "<<val<<" , ";
        }
        cout<<endl;
    }
    private:
        unordered_map<int, typename list<pair<int,int>>::iterator> key_iter;
        list<pair<int,int>> cache;
};

int main(){
    LRUCache<2> lru;
    lru.put(1,10);
    lru.put(2,20);
    lru.print();
    cout<<lru.get(1)<<endl;
    lru.print();
    lru.put(3,30);
    lru.print();
    cout<<lru.get(1)<<endl;
    lru.print();
    lru.put(1,100);
    lru.print();
    lru.put(2,200);
    lru.print();
}