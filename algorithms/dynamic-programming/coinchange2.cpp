/*
 Coin Change: Number of Ways
Count the number of ways to make up a given amount using the available denominations.

Problem Statement:
Given an integer array coins and an integer amount, return the number of combinations to make up that amount.

*/
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>
using namespace std;

int coinChangeWays(vector<int> &coins, int amount){
    vector<int> dp(amount+1,0);
    dp[0]=1;

    for (const int coin: coins){
        for (int i=coin;i<amount+1;++i){
            dp[i]+=dp[i-coin];
        }
    }

    copy(dp.begin(), dp.end(), ostream_iterator<int>(cout,","));
    cout<<endl;
    return dp[amount];
}


int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    cout << "Number of ways: " << coinChangeWays(coins, amount) << endl; // Output: 4
    assert(coinChangeWays(coins, amount)==4);
    
    return 0;
}