#include <iostream>
#include <utility>
#include <string>

using namespace std;

void print_glvalue(string &s) { cout<<"glvalue "<<s<<endl;}
void print_prvalue(string s) { cout<<"prvalue "<<s<<endl;}
void print_xvalue(string &&s) { cout<<"xvalue "<<s<<endl;}

int main(){
    string s("abc");
    print_glvalue(s);
    print_prvalue("deg");
    print_xvalue(std::move(s));
    return 0;
}