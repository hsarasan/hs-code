#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

int main(){
    vector<string> v;
    ifstream ifs("temp.txt");
    copy(istream_iterator<string>(ifs), 
        istream_iterator<string>(),
        back_inserter(v)  );
    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), ostream_iterator<string>(cout,","));
} 