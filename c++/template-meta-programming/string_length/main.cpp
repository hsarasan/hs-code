#include <iostream>


using namespace std;

template <size_t N>
int string_length(const char (&str)[N]){
    return N-1;
}

int main(){
    int n=string_length("Hello World!");
    cout<<n<<endl;
    return 0;
}