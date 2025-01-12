/*
Partition (problem)
Given an array of strictly positive integers arr, 
check if we can split it into two subsets that have the same sum of elements.

Example 1:
input:
arr = [4, 5, 3, 2, 5, 1]
output: true
explanation: We can split arr into [4, 3, 2, 1] and [5, 5], and they have the same sum
4+3+2+1 = 5+5 = 10

Example 2:
input:
arr = [5, 6, 2, 3, 8, 1]
output: false
explanation: We can't split arr into two subsets that have the same sum

Constraints:

len(arr) >= 1
arr[i] >= 1

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <algorithm>

using namespace std;

bool isPartitionPossible(const vector<int> & v){
    int n=v.size();
    int target=reduce(v.begin(), v.end());
    if (target%2==1) return false;
    target = target/2;
    vector< vector<int>> dp(n,vector<int>(target+1,0));
    dp[0][v[0]]=1;
    for (int i=1;i<n;++i){
        for (int j=0;j<target+1;++j){
            int value=v[i];
            if (j==value) {
                dp[i][j]=1;
            }
            else if (dp[i-1][j]==1){
                dp[i][j]=1;
            }
            else if (j>value){
                dp[i][j]=dp[i-1][j-value];
            }
            if (dp[i][target]==1) return true;
        }
    }
    return false;
}

int main(){
    vector<int> arr = {4, 5, 3, 2, 5, 1};
    bool b = isPartitionPossible(arr);
    cout<<b<<endl;
    arr = {5, 6, 2, 3, 8, 1};
    b = isPartitionPossible(arr);
    cout<<b<<endl;
    arr = {4,8,80,800};
    b = isPartitionPossible(arr);
    cout<<b<<endl;
    arr = {4,8,12,16};
    b = isPartitionPossible(arr);
    cout<<b<<endl;
}