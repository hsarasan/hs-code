/*
Problem: 
Given a 2d matrix cost[][], the task is to calculate the minimum cost path to reach (m, n) from (0, 0).
Each cell of the matrix represents a cost to traverse through that cell. 
The total cost of a path to reach (m, n) is the sum of all the costs on that path 
(including both source and destination).
We can only traverse down, right and diagonally lower cells from a given cell, i.e.,
 from a given cell (i, j), cells (i+1, j), (i, j+1), and (i+1, j+1) can be traversed
*/
#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <algorithm>

using namespace std;

int cost_function(std::vector<std::vector<int>> &cost){
    int m=cost.size();
    int n=cost[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    //initialise
    dp[0][0]=cost[0][0];
    for (int i=1;i<n;++i){
        dp[0][i]=dp[0][i-1]+cost[0][i];
    }
    for (int j=1;j<m;++j){
        dp[j][0]=dp[j-1][0]+cost[j][0];
    }
    for (int i=1;i<m;++i)
    for (int j=1;j<n;++j){
        int min_dp = min( min(dp[i-1][j-1],dp[i-1][j]), dp[i][j-1]);
        int min_cost=min_dp+cost[i][j];
        dp[i][j]=min_cost;
    }
    for (int i=0;i<m;++i){
        copy(dp[i].begin(), dp[i].end(), ostream_iterator<int>(cout,","));
        cout<<endl;
    }
    return dp[m-1][n-1];
}


int main(){
    std::vector<std::vector<int>> cost={
        {3,2,12,15,10},
        {6,19,7,11,17},
        {8,5,12,32,21},
        {3,20,2,9,7}
    };
    int min_cost = cost_function(cost);
    cout<<"min_cost="<<min_cost<<endl;
    assert(min_cost==100);
}