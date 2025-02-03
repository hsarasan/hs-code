#include <iostream>
#include <boost/scoped_ptr.hpp>

using namespace std;

int main(){
    boost::scoped_ptr ptr{new int[1]};
    cout<<boolalpha<<static_cast<bool>(ptr)<<endl;
    ptr.reset(nullptr);
    cout<<boolalpha<<static_cast<bool>(ptr)<<endl;
}