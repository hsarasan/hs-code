#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <list>
#include <string>

using namespace std;
using Person=pair<string,string>;

bool comparator(const pair<string,string> &person1, const pair<string,string> & person2){
    return person1.second < person2.second || 
            (person1.second==person2.second && person1.first<person1.first);
}

namespace std{

ostream & operator<<(ostream & o, const pair<string,string> & p){
    o<<p.second<<","<<p.first;
    return o;
}
};

int main(){
    vector<pair<string,string>> v;
    v.push_back({"thomas","sebastian"});
    v.push_back({"average","joe"});
    v.push_back({"tom","dick"});
    sort(v.begin(), v.end(), comparator);
    copy(v.begin(), v.end(), ostream_iterator<Person> (cout,"\n"));
    std::cout<<std::endl;
}

