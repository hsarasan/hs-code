/*
Coin Change: Minimum Coins
Find the minimum number of coins required to make up a given amount, or determine if it's not possible.

Problem Statement:
Given an integer array coins representing denominations of coins and an integer amount, return the minimum number of coins needed to make up that amount. 
If it's not possible, return -1.
*/
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;

int coinChange(vector<int> & coins, int amount){
    vector<int> dp(amount+1, 0);
    dp[0]=1;
    for ( int i=1; i<amount+1; ++i){
        int no_of_ways=INT_MAX;
        for (const int coin: coins){
            if (coin==i) {
                no_of_ways=1;
                break;
            }
            if (i>coin){
                if (dp[i-coin]>0)
                    no_of_ways=min(no_of_ways, 1+dp[i-coin]);
            }
        }
        if (no_of_ways==INT_MAX) no_of_ways=0;
        dp[i]=no_of_ways;
    }

    return dp[amount];

}


int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    assert(coinChange(coins, amount)==3);
    return 0;
}