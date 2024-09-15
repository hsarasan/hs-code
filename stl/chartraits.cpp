#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <queue>
#include <forward_list>
#include <set>
#include <functional>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;
using namespace std::placeholders;

struct caseinsensitive_chartraits : public char_traits<char>{
    static bool lt(const char  a, const char b){
        return tolower(a)<tolower(b);
    }
};

int main(){
    
    basic_string<char,caseinsensitive_chartraits> s;
    

}
