#include <bits/stdc++.h>

using namespace std;

struct compare{
    bool operator()(const pair<int,int>& p1, const pair<int,int>& p2 )const{
        return p1.second<p2.second;
    }
};

void printNMostFrequentWords(vector<int> & v, int n){
    unordered_map<int,int> hash_map;
    for (const auto & item: v){
        hash_map[item]++;
    }
    priority_queue<pair<int,int>, vector<pair<int,int>> , compare> PQ;
    for (const auto & [k,v]: hash_map){
        cout<<k<<"=>"<<v<<endl;
        PQ.push({k,v});
    }
    cout<<PQ.top().first<<endl;
    PQ.pop();
    cout<<PQ.top().first<<endl;
}

int main(){
    vector<int> v{5,2,4,7,2,2,3,5,7,3,5,8,4,2,46,5,3,9};
    printNMostFrequentWords(v,3);
}