#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main(){
    vector<int> v{1,2,3,4};
    auto sqr=[](int num) { return num*num; };
    auto squared_view = std::views::transform(v,sqr);
    for (const auto & sqr: squared_view)
        cout<<sqr<<endl;
}