/*
Given two strings word1 and word2, calculate their edit distance.
The edit distance in this problem is defined as the minimum number of insertions, 
deletions, and substitutions of characters to go from word1 to word2.

input:
word1 = "inside"
word2 = "index"

output: 3
*/
#include <vector>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int getEditDistance(string s1, string s2){
    int m=s1.size();
    int n=s2.size();
    vector<vector<int>> dp(m, vector<int>(n,0));
    if (s1[0]!=s2[0]) dp[0][0]=1;
    for (int i=1; i<m; ++i){
        dp[0][i]=1+dp[0][i-1];
    }
    for (int j=1; j<n; ++j){
        dp[j][0] = 1+dp[j-1][0];
    }
    for (int i=1;i<m;++i)
    for (int j=1;j<n;++j){
        if (s1[i]==s2[j]){
            dp[i][j]=dp[i-1][j-1];
        }
        else{
            dp[i][j]=1+min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));
        }
    }
    return dp[m-1][n-1];
}

int main(){
    assert(getEditDistance("inside","index")==3);
}

