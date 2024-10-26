#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

int main(){
    priority_queue<int,vector<int>,greater<int>> PQ;
    PQ.push(1);
    PQ.push(2);
    PQ.push(3);
    cout<<PQ.top()<<endl;
    assert(PQ.top()==1);
}