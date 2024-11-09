#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

template <typename T, typename... Args>
T sum(T a, Args... args)
{
   if constexpr (sizeof...(args) == 0)
      return a;
   else
      return a + sum(args...);
}
int main(){
    cout<<sum(7,4,3,2)<<endl;
    cout<<sum(string("def"),string("abc"),string("jki"))<<endl;
    cout<<sum(7,9)<<endl;
}
