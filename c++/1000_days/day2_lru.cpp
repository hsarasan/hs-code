/* Implement a lru cache */

#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>
#include <string>

using namespace std;

template <typename KeyType, typename ValueType>
class LRUCache {

    public:
    explicit LRUCache(int capacity):capacity(capacity){}
    void printCache() {
        for (const auto & p: cache ) {
            cout << p.first << "=>" << p.second << "  ";
        }
        cout << endl;
    }
    void insert(const KeyType& key, const ValueType& value) {

        if (cacheMap.find(key) != cacheMap.end()) {
            cacheMap[key]->second = value;
            moveToFront(key);
            return ;
        }
        if (cache.size()==capacity) {
            deleteFromLast();
        }
        cache.push_front({key,value});
        cacheMap[key]=cache.begin();
    }
    ValueType get(const KeyType& key) {
        auto iter=cacheMap.find(key);
        if (iter==cacheMap.end()) {
            return ValueType();
        }
        auto cache_iter=iter->second;
        auto ret = cache_iter->second;
        moveToFront(key);
        return ret;
    }

private:
    void moveToFront(KeyType key) {
        auto iter=cacheMap[key];
        if (iter == cache.begin()) return;
        cache.splice(cache.begin(),cache,iter);
    }
    void deleteFromLast() {
        auto iter=cache.back();
        auto key=iter.first;
        cacheMap.erase(key);
        cache.pop_back();
    }
    int capacity;
    list<pair<KeyType,ValueType>> cache;
    using ListIterator = typename list<pair<KeyType,ValueType>>::iterator;
    unordered_map<KeyType, ListIterator> cacheMap;

};

int main() {
    LRUCache<int,string> lru(3);
    lru.insert(1,"one");
    lru.insert(2,"two");
    lru.insert(3,"three");
    lru.printCache();
    lru.insert(4, "four");
    lru.printCache();
    lru.insert(2,"TWO");
    lru.printCache();
    return 0;
}