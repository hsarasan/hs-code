#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ifstream ifs("crtp.cpp", ios::ate);
    cout<<ifs.tellg()<<endl;
    auto size=ifs.tellg();
    if (size>100){
        string content(100,0);
        ifs.seekg(0);
        ifs.read(&content[0],100);
        cout<<content<<endl;
    }
}