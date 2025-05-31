#include <iostream>
#include <string>
#include <compare>
#include <unordered_set>

using namespace std;

struct Person{
    string name;
    int id;
    auto operator<=>(const Person &p) const =default;
    
};
template <>
struct std::hash<Person>{
    size_t operator()(const Person &p) const {
        return hash<string> {}(p.name);
    }
};


int main(){
    Person p1{"abc",1};
    Person p2{"ABC",2};
    unordered_set<Person> people;
    people.insert(p1);
    people.insert(p2);
    std::cout<<"Size="<<people.size()<<std::endl;
}