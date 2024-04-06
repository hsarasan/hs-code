#include <vector>
#include <algorithm>
#include <iostream>

/* Problem:
Given information about stock prices as std::vector<int> 
where each element represents the price at that time, 
determine the maximum possible profit achievable 
with two transactions.

You can only hold one stock at a time and only 
do one buy or sell operation at each time.
*/

// Your solution:
int maximum_profit(const std::vector<int>& prices) {
    std::vector<int> best_price_after_today(prices.size(),0);
    std::vector<int> best_profit_today(prices.size(),0);
    auto n=prices.size();
    best_price_after_today[n-1]=prices[n-1];
    for (size_t i=n-2;i>0;--i){
        best_price_after_today[i]=std::max(best_price_after_today[i+1],prices[i]);
    }
    best_price_after_today[0]=std::max(best_price_after_today[1],prices[1]);
    for (size_t i=0;i<n-1;++i){
        best_profit_today[i]=best_price_after_today[i]-prices[i];
    }
    int total_profit=0;
    int sub_profit=0;
    for (const auto & profit: best_profit_today){
        if (profit==0){
            total_profit+=sub_profit;
            sub_profit=0;
        }
        else{
            sub_profit=std::max(sub_profit,profit);
        }
    }
    return total_profit;
}

#include <cassert>

int main() {
    assert(maximum_profit({1}) == 0);
    assert(maximum_profit({1,2}) == 1);
    assert(maximum_profit({1,2,3,4,5}) == 4);
    assert(maximum_profit({5,4,3,2,1}) == 0);
    assert(maximum_profit({0,0,9,1,2,3,4,5,0,9}) == 18);
    assert(maximum_profit({0,9,1,2,3,4,5,0,9}) == 18);
    assert(maximum_profit({0,9,1,2,3,4,5,0}) == 13);
    assert(maximum_profit({0,9,1,5,0,3}) == 16);
}