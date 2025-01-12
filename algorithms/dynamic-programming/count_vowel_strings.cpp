/*
Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted. A string s is lexicographically sorted if each character comes before or same as the next one in the alphabet.
Example 1:

Input: n = 2
Output: 15
Explanation: sorted vowel strings of size 2 are:
aa, ae, ai, ao, au, ea, ee, ei, eo, eu, ii, io, iu, oo, ou, uu

Example 2:
Input: n = 9
Output: 715

Constraints:
n >= 1
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int getNoOfVowelStrings(int n){
    vector < vector<int> > dp(5,vector<int>(n+1,0));
 
    for (int i=0;i<5;++i) dp[i][1]=1;
    for (int i=2; i<n+1; ++i){
        dp[0][i]=dp[0][i-1]+dp[1][i-1]+dp[2][i-1]+dp[3][i-1]+dp[4][i-1];
        dp[1][i]=dp[1][i-1]+dp[2][i-1]+dp[3][i-1]+dp[4][i-1];
        dp[2][i]=dp[2][i-1]+dp[3][i-1]+dp[4][i-1];
        dp[3][i]=dp[3][i-1]+dp[4][i-1];
        dp[4][i]=dp[4][i-1];
    }
    int val=0;
    for (int i=0;i<5;++i)
        val=val+dp[i][n];
    return val;
}

int main(){
    int n=getNoOfVowelStrings(2);
    cout<<n<<endl;
    n=getNoOfVowelStrings(9);
    cout<<n<<endl;
    return 0;
}