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

using namespace std;
using namespace std::placeholders;

int main(){
    vector<int> v{1,2,3,4};
    vector<int> v2;
    transform(v.begin(), v.end(), back_inserter(v2), bind(multiplies<int>(),_1,10));
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout,","));
}

