#include <iostream>
#include <list>
#include <iterator>


using namespace std;
 
template <typename C>
void print(const C& c){
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout,","));
    cout<<endl;
}

int main(){

    list<int> li({1,2,4,5});
    print(li);

}