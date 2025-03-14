#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

bool compare(const pair<int,int>& p1, const pair<int,int>& p2){
    if (p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first<p2.first;
}

int findNumberOfOverlappingIntervals(vector<vector<int>> &intervals){
    
    vector<pair<int,int>> events;
    for (const auto & interval: intervals){
        events.push_back({interval[0],1});
        events.push_back({interval[1],-1});
    }
    sort(events.begin(), events.end(), compare);
    int max_overlap{0};
    int overlap=0;
    for(const auto & event: events){
        overlap=overlap+event.second;
        max_overlap=max(max_overlap,overlap);
    }
    return max_overlap;
}

int main(){
    vector<vector<int>> intervals{{30,75},{0,50},{60,150}};
    cout<<findNumberOfOverlappingIntervals(intervals);
}