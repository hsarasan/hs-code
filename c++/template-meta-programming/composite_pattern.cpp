#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

struct HeroGroup;
struct Hero;

template <typename T>
struct Helper{
    static void printAllMembers(const T& t){ t.printAllMembers();}
};
template <typename T1, typename T2>
void makeFriends(T1 & a, T2 &b){
    a.addFriend(b);
    b.addFriend(a);
} 
struct Hero{
        Hero(const string &name_):name(name_){}
        void addFriend(HeroGroup &h) {
            groups.emplace_back(h);
        }
        void addFriend(Hero & h)  {
            heroes.emplace_back(h);
        }
        void printFriends(){
            for (const auto & hero: heroes){
                cout<<hero.name<<",";
            }
            for (const auto & group: groups){
                Helper<HeroGroup>::printAllMembers(group);
            }
            cout<<endl<<"================="<<endl;
        }
        string name;
        vector<Hero> heroes;
        vector<HeroGroup> groups;
};
struct HeroGroup{
    
    HeroGroup(const string &name_):name(name_){}
    void addFriend(Hero & h){heroes.emplace_back(h);}
    void addHero(Hero &h) { heroes.emplace_back(h); }
    void printAllMembers()const {
        for (const auto & hero: heroes){
            cout<<hero.name<<",";
        }
    }
    void printFriends(){
        for (const auto & hero: heroes){
            cout<<hero.name<<",";
        }
        for (const auto & group: groups){
            group.printAllMembers();
        }
        cout<<endl<<"=================="<<endl;
    }
        vector<Hero> heroes;
        vector<HeroGroup> groups;
        string name;
};


int main(){
    Hero a("abc");
    Hero b("def");
    Hero c("ksdf");
    HeroGroup G1("G!");
    G1.addHero(c);

    makeFriends(a,b);
    makeFriends(a,c);
    makeFriends(G1,b);
    a.printFriends();
    b.printFriends();
    c.printFriends();
    return 0;
}