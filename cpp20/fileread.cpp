#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

template <typename T>
void print(const std::vector<T> & v){
    std::ranges::copy(v,std::ostream_iterator<T>(std::cout," "));
}
int main(){
    std::ifstream ifs("sample.txt");
    std::vector<std::string> strings;
    std::ranges::istream_view<std::string> isv(ifs);
    for (const auto & str: isv) {
        auto parts = str| std::views::split(',');
        for (const auto & part : parts){
            strings.emplace_back(part.begin(),part.end());
        }
    }
    print(strings);
}  