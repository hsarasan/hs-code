/*
Given a stairs with n steps and a list of possible ways to jump (for example if jumps[i] = 4 
then it's possible to jump by 4 steps), 
find the total number of ways to reach the nth step starting from the floor.
input:
n = 10
jumps = [2, 4, 5, 8]

output: 11
*/
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

int getNoOfWays(vector<int> jumps, int steps){
    vector<int> dp(steps+1,0);
    for (int i=1; i<steps+1; ++i){
        int count_for_this_step=0;
        for (const auto jump: jumps){
            if (jump==i){
                count_for_this_step++;
            }
            else if (jump<i){
                count_for_this_step=count_for_this_step+dp[i-jump];
            }
        }
        dp[i]=count_for_this_step;
    }
    return dp[steps];
}

int main(){
    assert(getNoOfWays({2,4,5,8},10)==11);
}