#include <iostream>
#include <functional>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
using namespace std;
using namespace std::views;

template <typename T>
void print(const vector<T> & v){
    std::ranges::copy(v,std::ostream_iterator<T>(std::cout," "));
}
int main(){
    std::string s="a,bc,d";
    auto parts=s|std::views::split(',');
    std::vector<string> strings;
    for ( const auto & part : parts){
        strings.emplace_back(part.begin(), part.end());
    }
    print(strings);
}  