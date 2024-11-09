#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T>
concept associative_container = requires (T t){
    typename T::value_type;
    typename T::key_type;
    typename T::mapped_type;
};
template <typename T>
concept sequence_container = requires (T t){
    typename T::value_type;
    t.begin();
    t.end();
} && !associative_container<T>;

template <associative_container C>
void log(const C & c){
    for (const auto & [k,v]: c)
        cout<<k<<"=>"<<v<<" ";
    cout<<endl;
};
template <sequence_container C>
void log (const C & c){
    using T = C::value_type;
    copy(c.begin(), c.end(), ostream_iterator<T>(cout,","));
    cout<<endl;
} ;

template <typename T>
void log(const T & t){
    cout<<"Logging not implemented for this type "<<endl;
}


int main(){
    vector<int> v{1,2,3,4};
    map<int,string> m{ {1,"one"},{2,"two"}};
    log(v);
    log(m);
    log("abc");
    return 0;
}