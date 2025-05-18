#include <iostream>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    cout<<is_same_v<size_t,vector<int>::size_type><<endl;
    cout<<is_same_v<int,vector<int>::size_type><<endl;
}