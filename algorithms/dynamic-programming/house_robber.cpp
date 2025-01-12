/*
Given an array of integers arr where arr[i] represents the amount of money in the house i, 
you are asked to find the maximum amount of money that a robber can steal knowing that he 
can't steal two adjacent houses because the security systems would automatically call the police
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;
int get_max_steal(const vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n+1,0);
    dp[0]=0;
    if (n==1) return arr[0];
    if (n==2) return max(arr[0],arr[1]);
    if (n==3) return max(arr[0]+arr[2],arr[1]);
    dp[0]=0;
    dp[1]=arr[0];
    dp[2]=max(arr[0],arr[1]);
    dp[3]=max(arr[0]+arr[2],arr[1]);
    for (int i=4;i<n+1;++i){
        dp[i]=max(dp[i-2]+arr[i],dp[i-1]);
    }
    return dp[n];
}


std::vector<int> arr{2, 10, 3, 6, 8, 1, 7};

int main(){
    int n=get_max_steal(arr);
    assert(n==25);
}