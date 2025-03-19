#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

int main(){
    unordered_set<int> S;
    for (int i=0;i<10000;++i) S.insert(i);
    cout<<"# of buckets = "<<S.bucket_count()<<endl;
    cout<<"LF="<<S.load_factor()<<endl;
    for (const auto elem: S){
        if (S.bucket_size(S.bucket(elem))>1){
            cout<<elem<<"  ";
        }
    }
}