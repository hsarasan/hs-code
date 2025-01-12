/*
Given a mine of n rows and m columns where mine{i}{j} represents the amount of gold
that is present there, we want to enter from the top of the mine and take as much 
gold as possible when exiting from the bottom, knowing that we can only move to the bottom, 
to the bottom-left, or to the bottom-right. We can exit from anywhere from the last row

*/
#include <vector>
#include <iostream>
#include <iterator>
#include <cassert>
#include <algorithm>

using namespace std;
std::vector<vector<int>> mine = {
   {3, 2, 12, 15, 10},
   {6, 19, 7, 11, 17},
   {8, 5, 12, 32, 21},
   {3, 20, 2, 9, 7}
};

int getGold(std::vector<vector<int>> & mine){
    int m=mine.size();
    int n=mine[0].size();
    vector< vector<int>> dp(m,vector<int>(n,0));
    for (int i=0; i<n; ++i){
        dp[0][i]=mine[0][i];
    }
    for (int i=1;i<m;++i)
    for (int j=0;j<n;++j){
        if (j==0){
            dp[i][j]=mine[i][j]+max(dp[i-1][j],dp[i-1][j+1]);
        }
        else if (j==n-1){
            dp[i][j]=mine[i][j]+max(dp[i-1][j],dp[i-1][j-1]);
        }
        else{
            dp[i][j]=mine[i][j]+max(dp[i-1][j-1],max(dp[i-1][j],dp[i-1][j+1]));
        }
    }
    return *max_element(dp[m-1].begin(), dp[m-1].end());
}

int main(){
    assert(getGold(mine)==73);
}