/*
Shortest common supersequence (problem)
Given two strings s1 and s2, find the length of their shortest common supersequence,
the shortest string that has both s1 and s2 subsequences.
A string A is a supersequence of a string B if B is a subsequence of A.

Example:

input:
s1 = "abdacebfcab"
s2 = "acebfca"
output: 11

*/

//TIP -> SCS (S1,S2)=S1+S2-LCS(S1,S2)
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

int getSCS(string s1, string s2){
    int m=s1.size();
    int n=s2.size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    if (s1[0]==s2[0]) dp[0][0]=1;

    for (int i=1; i<n; ++i){
        if (s1[0]==s2[i]){
            dp[0][i]=1;
        }
        else {
            dp[0][i]=dp[0][i-1];
        }
    }
    for (int i=1; i<m; ++i){
        if (s1[i]==s2[0]){
            dp[i][0]=1;
        }
        else {
            dp[i][0]=dp[i-1][0];
        }
    }
    for (int i=1;i<m;++i)
    for (int j=1;j<n;++j){
        if (s1[i]==s2[j]){
            dp[i][j]=1+dp[i-1][j-1];
        }
        else{
            dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return m+n-dp[m-1][n-1];
}


int main(){
    string s1 = "abdacebfcab";
    string s2 = "acebfca";
    int n=getSCS(s1,s2);
    assert(n==11);
}