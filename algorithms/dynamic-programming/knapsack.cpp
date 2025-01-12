/*
0-1 knapsack (problem)
Given the value and the weight of each one of n items, we want to maximize the value of items we take in our knapsack without exceeding its capacity k. 
You are asked to find the maximum total value that we can get without exceeding a total weight of k.
Note that each item can be took at most once.
*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int knapsack(vector<int>& values, vector<int>& weights, int max_weight){
    int m=weights.size();
    int n=max_weight;
    vector<vector<int>> dp(m,vector<int>(n,0));
    for (int i=weights[0]; i<n; ++i){
        dp[0][i]=values[0];
    }
    for (int i=1; i<m; ++i)
    for (int j=0; j<n; ++j){
        if (weights[i]<j){
            dp[i][j]=max(dp[i-1][j], values[i]+dp[i-1][j-weights[i]]);
        }
        else{
            dp[i][j]=dp[i-1][j];
        }
    }
    return dp[m-1][n-1];
}
int main(){
    vector<int> values{20, 30, 15, 25, 10};
    vector<int> weights{6, 13, 5, 10, 3};
    int k = 20;
    assert(knapsack(values,weights,k)==55);
}