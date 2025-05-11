#include <iostream>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

template <typename C>
void print(const C& c) {
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type> (cout," "));
    cout<<endl;
}

int main(){
    vector<int> v{1,2,3,4};
    print(v);
    return 0;
}