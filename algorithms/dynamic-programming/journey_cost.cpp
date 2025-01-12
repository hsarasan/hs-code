/*
Minimum cost for tickets (problem)
We are about to travel for a period of n days, during which we will use the train in some days 
that you can find in a given set train_days.
And to use the train, we have to possess either a 1-day pass, a 7-days pass, or a 30-days pass,
each one of them has a price that you can find in a given array prices, 
where prices[0] represents the price of a 1-day pass, prices[1] represents the price of a 7-days pass, 
and prices[2] represents the price of a 30-days pass.
You are asked to find the minimum amount of money that we need to use 
the train during all the train days.

Example:
input:
train_days = [1, 3, 8, 9, 22, 23, 28, 31]
costs = [4, 10, 25]
n = 32

output: 28

explanation: The cheapest way is by buying
a 1-day pass on day 1, we use it on day 1
a 7-days pass on day 3, we use it during days 3, 8, and 9
a 7-days pass on day 22, we use it during days 22, 23, and 28
a 1-day pass on day 31, we use it on day 31
costs[0]+costs[1]+costs[1]+costs[0] = 4+10+10+4 = 28

Constraints:
n > 0
train days are between 0 inclusive and n exclusive
len(costs) == 3*/

#include <iostream>
#include <vector>

using namespace std;

int getMinimumCost(vector<int> train_days, vector<int> costs){
    int n=train_days[train_days.size()-1];
    vector<int> travel_days_dp(n+1,0);
    for (const auto train_day: train_days){
        travel_days_dp[train_day]=1;
    }
    vector<int> dp(n+1,0);
    for (int i=1; i<n+1;++i){
        if (travel_days_dp[i]==0){
            dp[i]=dp[i-1];
            continue;
        }
        int earliest_day_to_buy_weekly=max(i-7,0);
        int earliest_day_buy_monthly=max(i-30,0);
        dp[i]=min( dp[i-1]+costs[0],
                   min(dp[earliest_day_buy_monthly]+costs[2],
                       dp[earliest_day_to_buy_weekly]+costs[1]));
    }
    return dp[n];
}


int main(){
    vector<int> train_days = {1, 3, 8, 9, 22, 23, 28, 31};
    vector<int> costs = {4, 10, 25};
    int n=getMinimumCost(train_days, costs);
    cout<<n<<endl;
    return 0;
}