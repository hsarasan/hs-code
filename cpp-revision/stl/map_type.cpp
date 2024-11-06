#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

template <typename Container>
void func(Container & c){
    using K=typename Container::key_type;
    using V=typename Container::mapped_type;
    K k{};
    V v{};
    cout<<v<<endl;
    c[k]=v;
}

int main(){
    map<int,string> m;
    m[1]="one";
    func(m);
    for (const auto & [k,v]: m)
        cout<<k<<"="<<v<<" ";
    cout<<endl;
    return 0;
   
}