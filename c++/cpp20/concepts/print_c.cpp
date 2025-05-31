#include <iostream>
#include <vector>

using namespace std;

template <typename C>
void print(C c){
    for (const auto & v: c){
        cout<<v<<endl;
    }
}

int main(){
    vector<int> v{1,2,3,4};
    print(v);
    return 0;
}