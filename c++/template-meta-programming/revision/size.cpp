#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

template <typename... Args>
array<int,sizeof...(Args)> getTypeSizes(Args... args){
    return {sizeof(args)...};
}

int main(){
    auto ar=getTypeSizes(1,1.23,"abc",std::string("abcd"));
    copy(ar.begin(),ar.end(),ostream_iterator<int>(cout,","));
    return 0;
}