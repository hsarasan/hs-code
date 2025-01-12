#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

template <typename K, typename V>
class HashMap{
    public:
    HashMap(int size=5):size(size){
        table.resize(size);
    }
    HashMap(const HashMap &) = default;
    HashMap(HashMap && )=default;
    void put(const pair<K,V> & p){
        int index = getHashKey(p.first);
        auto & elem = table[index];
        auto iter=find(elem.begin(), elem.end(), p);
        if (iter==elem.end()){
            table[index].emplace_back(p);
        }
        else{
            iter->second=p.second;
        }
        
    }

    V  get(const K & key){
        int index = getHashKey(key);
        auto & elem = table[index];
        auto iter=find_if(elem.begin(), elem.end(), [=]( pair<K,V>& p){
          return p.first==key;  
        });
        if (iter==elem.end()){
            V v;
            K k(key);
            pair<K,V> p(k,v);
            elem.emplace_back(p);
            return V();
        }
        else{
            return iter->second;
        }
    }

    void printHashTable(){
        for (const auto & elem: table){
            for (const auto &p : elem){
                std::cout<<"{"<<p.first<<","<<p.second<<"},";
            }
            std::cout<<std::endl;
        }
    }

    private:
        int getHashKey(const K & key){
            auto hash_value = hash<K>{}(key);
            std::cout<<"Hash Value "<<hash_value<<std::endl;
            return hash_value%size;
        }
        vector< list<pair<K,V>>> table;    
        int size;
};

int main(){
    HashMap<int,string> HM;
    HM.put({1,"one"});
    HM.put({2,"two"});
    HM.put({3,"three"});
    HM.put({3,"threethree"});
    HM.printHashTable();
    auto x = HM.get(3);
    std::cout<<x<<std::endl;
    x = HM.get(4);
    std::cout<<x<<std::endl;
    HM.printHashTable();

}