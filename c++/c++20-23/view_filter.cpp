#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main(){
    vector<int> v{1,2,3,4};
    auto isEven=[](int num) { return num%2==0; };
    auto even_only = std::views::filter(v,isEven);
    for (const auto & sqr: even_only)
        cout<<sqr<<endl;
}