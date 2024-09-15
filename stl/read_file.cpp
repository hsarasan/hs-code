#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

template <typename C>
void print(const C& c){
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout,","));
}


int main(){

    ifstream ifs("read_file.cpp");
    vector<string> v{istream_iterator<string>(ifs), istream_iterator<string>()};
    print(v);

}