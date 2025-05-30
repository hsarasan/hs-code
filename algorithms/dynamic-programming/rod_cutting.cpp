/*
We want to sell a rod of size n, and to maximize the profit, we can cut it into multiple pieces.
The price of a piece depends on its length, to know it, we are given an array prices where prices[i] represents the price of a piece of length i.
You are asked to find the maximum price that we can get by cutting it into pieces.
Note that you are allowed to sell it as a single piece of length n if it's the most profitable choice.

Example:
input:
n = 8
prices = [0, 1, 3, 5, 6, 7, 9, 10, 11]
output: 13

explanation: The most profitable way of cutting a rod of length 8 with the given prices is
by cutting it into a piece of length 2 and two pieces of length 3
prices[2]+prices[2]+prices[3] = 3+5+5 = 13

Constraints:

n > 0
len(prices) == n+1
prices[0] == 0
prices[i] >= 0
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int getMaxProfit(const vector<int> & prices){
    int n=prices.size();
    vector<int> dp(n+1,0);
    dp[0]=prices[0];
    for (int i=1; i<n+1; ++i){
        int profit=0;
        for (int j=0;j<i;++j){
            profit = max(profit, dp[i-j]+prices[j]);
        }
        dp[i]=profit;
    }
    return dp[n];
}


int main(){
    vector<int> prices = {0, 1, 3, 5, 6, 7, 9, 10, 11};
    int n=getMaxProfit(prices);
    cout<<n<<endl;
}



