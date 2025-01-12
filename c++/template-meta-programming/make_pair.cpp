#include <iostream>
#include <utility>
#include <string>
#include <cstring>

using namespace std;

struct my_string{
    char * data;
    int size;
    my_string(const char * value){
        cout<<"my_string()"<<endl;
        data = new char[strlen(value)+1];
        size = strlen(value);
        strcpy(data,value);
    }
    friend void swap(my_string & s1, my_string & s2) noexcept {
        std::swap(s1.data, s2.data);
        std::swap(s1.size, s2.size);
    }
    my_string(const my_string & other){
        cout<<"my_string(copy)"<<endl;
        data = new char[other.size+1];
        strcpy(data, other.data);
        size = other.size;
    }
    my_string(my_string && other) noexcept{
        cout<<"my_string(move)"<<endl;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    ~my_string(){ delete[] data;}

    friend ostream & operator<<(ostream& o, const my_string & s){
        o<<s.data;
        return o;
    }
};

template <typename T1, typename T2>
auto my_make_pair(T1&& arg1, T2&& arg2){

    std::pair<decay_t<T1>,decay_t<T2>> p{std::forward<T1>(arg1), std::forward<T2>(arg2)};
    return p;
}

int main(){
    auto p = my_make_pair(1,4);
    cout<<p.first<<", "<<p.second<<endl;
    int v(10);
    string s("abc");
    auto p2 = my_make_pair(s,v);
    cout<<p2.first<<","<<p2.second<<endl;
    my_string s1("abcd");
    auto p3 = my_make_pair(s1,v);
    cout<<p3.first<<","<<p3.second<<endl;
    auto p4 = my_make_pair(std::move(s1),v);
    cout<<p4.first<<","<<p4.second<<endl;
    return 0;
}