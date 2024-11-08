#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

template <typename T> struct isLoggingSupported: std::false_type{};
template <typename T> struct isLoggingSupported<vector<T>>: std::true_type{};

template <typename Container>
std::enable_if_t< isLoggingSupported<Container>::value, void> 
log(const Container & c){
    using T = typename Container::value_type;
    copy(c.cbegin(), c.cend(), ostream_iterator<T>(cout,","));
    cout<<endl;
}

template <typename Container>
std::enable_if_t< !isLoggingSupported<Container>::value, void> 
log(const Container & c){
    cout<<"Logging not implemented "<<endl;
}



int main(){

    vector<int> v{1,2,3,4};
    log(v);
    list<int> l{1,2,3,4};
    log(l);
    return 0;
}
