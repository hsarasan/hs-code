#include <iostream>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    multimap<int,string> m;
    m.insert({0,"abc"});
    m.insert({0,"def"});
    m.insert({1,"ghi"});
    m.insert({1,"jkl"});
    m.insert({1,"mnop"});

    auto range=m.equal_range(1);
    for (auto it=range.first; it!=range.second; it++){
        cout<<it->first<<","<<it->second<<endl;
    }
    return 0;
}