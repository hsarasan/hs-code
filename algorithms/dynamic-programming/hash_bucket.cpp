#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

int main(){
    std::unordered_map<int, string> m;
    m[0]="zero";
    m[1]="one";
    cout<<m.bucket_count()<<" "<<m.load_factor()<<" "<<" "<<m.max_bucket_count()<<endl;
}