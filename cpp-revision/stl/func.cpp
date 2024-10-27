#include <iostream>
#include <functional>
#include <vector>

using namespace std;

using F=function<int(int,int)>;
int add(int a, int b){ return a+b;}

int main(){

    auto addx=[](int a,int b){ return a*b;};

    vector<F> v;
    v.emplace_back(add);
    v.emplace_back(addx);
    v.emplace_back( [](int a,int b){return a-b;});

    for (const auto & task: v){
        cout<<task(2,4)<<endl;
    }
}
