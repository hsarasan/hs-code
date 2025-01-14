#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

int main(){

    vector<string> names{"walter", "white", "jessie", "pinkman", "skyler","hank"};
    std::ranges::sort(names,{},&string::size);
    std::ranges::copy(names, ostream_iterator<string>(cout," "));
}