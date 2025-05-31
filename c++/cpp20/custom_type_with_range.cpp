#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

using namespace std;
struct Container{
    
    auto begin(){
        return v.begin();
    }
    auto end(){
        return v.begin()+3;
    }
    void print(){
        std::ranges::copy(v,ostream_iterator<int>(cout," "));
        cout<<endl;
    }
    vector<int> v{5,4,3,2,1};
};

int main(){
    Container c;
    std::ranges::sort(c);
    c.print();
}