#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
using namespace std;

int main(){

    vector<int> v = {1, 2, 3, 4, 5};
    auto it = std::find(v.begin(), v.end(), 3);
    auto it_4= std::find(v.begin(), v.end(), 4);
    v.erase(it);
    cout<<*it_4<<endl;
    assert(*it_4==5);
    return 0;

}