#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std;

template <typename Container>
void printContainer(const Container & c){
    using T=Container::value_type;
    copy(c.begin(), c.end(), ostream_iterator<T>(cout,","));
    cout<<endl;
}

int main(){
    list<string> l{"abc","def","geh"};
    printContainer(l);
}