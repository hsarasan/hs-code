/*
Longest common subsequence (problem)
Given two strings s1 and s2, find the length of their longest common subsequence.
A subsequence of a string s is a subset of its characters that are not necessarily 
adjacent but have to be in the right order.
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <cassert>

using namespace std;
int getLCS(string s1, string s2){
    int m=s1.size();
    int n=s2.size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    if (s1[0]==s2[0])
        dp[0][0]=1;
    for (int i=1;i<n;++i){
        if (s1[0]==s2[i])
            dp[0][i]=1;
        else 
            dp[0][i]=dp[0][i-1];
    }
    for (int i=1;i<m;++i){
        if (s1[i]==s2[0])
            dp[i][0]=1;
        else 
            dp[i][0]=dp[i-1][0];
    }
    for (int i=1; i<m; ++i)
    for (int j=1; j<n; ++j){
        if (s1[i]==s2[j]){
            dp[i][j]=1+dp[i-1][j-1];
        }
        else{
            dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m-1][n-1];
}

int main(){
    int lcs=getLCS("abdacbab","acebfca");
    assert(lcs==4);
}