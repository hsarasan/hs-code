#include <iostream>
#include <string>
#include <unordered_map>
#include <any>

class db_interface{
    public:
    std::unordered_map<std::string, std::any> hash_map;
    template <typename T>
    void set(const std::string &key, const T & value){
        hash_map[key]=value;
    }
    template <typename T>
    T get(const std::string &key){
        try{
            if (hash_map.count(key)==0) return T();
            auto value = hash_map[key];
            T ret = std::any_cast<T> (value);
            return ret;
        }
        catch(std::exception & e){
            std::cout<<e.what()<<std::endl;
        }
        return T();
    }
};

int main(){
    db_interface db;
    db.set("int",10);
    db.set("string",std::string("abc"));
    auto x = db.get<std::string>("string");
    std::cout<<x<<std::endl;
    auto y = db.get<std::string>("int");
    std::cout<<y<<std::endl;
    auto z = db.get<int>("int");
    std::cout<<z<<std::endl;
    auto any1 = db.get<int>("int");
    return 0;
}