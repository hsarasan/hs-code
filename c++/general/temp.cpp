#include <iostream>
#include <vector>


using namespace std;

void validate(int a, int b, int X){
	cout<<"final Validation "<<X<<endl;
    cout<<(a-b>X)<<endl;
}

template <typename... Args>
void validate(int a, int b, int X, Args... args){
    validate(a,b,X);
    validate(a,b,args...);
}


int main(){

    validate(1,2,8);
    cout<<"====="<<endl;
    validate(1,4,2,-2);
    cout<<"====="<<endl;
    validate(8,4,1,2,3,4,5,6);
}
