/*
Subset sum (problem)
Given an array arr of strictly positive integers, and an integer k, 
create a function that returns the number of subsets of arr that sum up to k.

Example 1:
input:
arr = [1, 2, 3, 1]
k = 4
output: 3
explanation: subsets that sum up to k are [1, 2, 1], [1, 3], and [3, 1]

Example 2:
input:
arr = [1, 2, 3, 1, 4],
k = 6
output: 4
explanation: subsets that sum up to k are [1, 2, 3], [1, 1, 4], [2, 3, 1], and [2, 4]

Example 3:
input:
arr = [2, 4, 2, 6, 8]
k = 7
output: 0
explanation: there are no subsets that sum up to k
*/

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;
int noOfSubsets(const vector<int> &v, int k){
    int n=v.size();
    vector< vector<int> > dp(n,vector<int>(k+1,0)); 
    int num=v[0];
    dp[0][num]=1;
    for (int i=1; i<n; ++i)
    for (int j=1; j<k+1; ++j){
        int value=v[i];
        if (j==value){
            dp[i][j]=1+dp[i-1][j];
        }
        else if (j>value){
            dp[i][j]=dp[i-1][j]+ dp[i-1][j-value];
        }
        else {
            dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n-1][k];
}

int main(){
    int n=noOfSubsets({1,2,3,1},4);
    assert(n==3);
    n=noOfSubsets({1,2,3,1,4},6);
    assert(n==4);
    n=noOfSubsets({2,4,2,6,8},7);
    assert(n==0);
    return 0;
}