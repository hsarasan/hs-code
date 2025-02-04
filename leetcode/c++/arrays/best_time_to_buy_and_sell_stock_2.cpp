/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
On each day, you may decide to buy and/or sell the stock. 
You can only hold at most one share of the stock at any time.
 However, you can buy it then immediately sell it on the same day.
Find and return the maximum profit you can achieve.
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {

public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        vector<int> dp(n+1,0);
        for (int i=2; i<n+1; ++i){
            dp[i]=dp[i-1];
            for (int j=1; j<i; ++j){
                dp[i]=max(  dp[i],
                            dp[j-1]+prices[i-1]-prices[j-1]
                        );
            }
        }
        return dp[n];
    }
};
int main(){
    Solution s;
    vector<int> prices={7,1,5,3,6,4};
    assert(s.maxProfit(prices)==7);
    prices={1,2,3,4,5};
    assert(s.maxProfit(prices)==4);
    prices={7,6,4,3,1};
    assert(s.maxProfit(prices)==0);
    prices={3,2,6,5,0,3};
    assert(s.maxProfit(prices)==7);
    return 0;
}