#include <iostream>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std::ranges;
using namespace std;

std::unordered_map<std::string, int> composers{
    {"Bach", 1685},
    {"Mozart", 1756},
    {"Beethoven", 1770},
    {"Tchaikovsky", 1840},
    {"Chopin", 1810},
    {"Vivaldi ", 1678},
};

int main() {
    auto v = composers
            | views::filter( [](const auto & p){ return p.second>1700 ;});
    vector<pair<string, int>> after_1700(v.begin(), v.end());
    auto cmp=[](const pair<string, int> & a,const pair<string, int> & b){
        return a.second<b.second ||
                a.second==b.second && a.first<b.first;
    };
    ranges::sort(after_1700,cmp);
    auto fin=after_1700
                | views::take(2)
                | views::keys;
    ranges::copy(fin,ostream_iterator<string>(cout,"\n"));
    return 0;
}