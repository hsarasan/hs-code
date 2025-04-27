#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Container>
void print( const Container &c){
    using element_type=typename Container::value_type;
    copy(c.begin(), c.end(), ostream_iterator<element_type>(cout," "));
    cout<<endl;
}

int main(){
    vector v{1,2,3,4,5};
    print(v);
    return 0;
}