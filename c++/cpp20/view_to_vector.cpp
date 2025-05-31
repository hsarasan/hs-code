#include <iostream>
#include <ranges>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main(){
    vector<int> v{1,2,3,4};
    auto sqr=[](int num) { return num*num; };
    auto squared_view = v|std::views::transform(sqr);
    auto squared_vec = vector<int>{};
    std::ranges::copy(squared_view,back_inserter(squared_vec));
    std::ranges::copy(squared_vec, ostream_iterator<int>(cout, " "));
}