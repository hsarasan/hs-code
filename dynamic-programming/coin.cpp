/*
Given an integer that represents an amount of money and a list of possible coins, find the minimum number of coins to make that amount.
Return -1 if it's possible to make the amount with the given coins.
Example:
input:
amount = 15
possible_coins = [2, 3, 7]
output: 4
explanation: We can make the amount 15 by taking 4 coins only, one coin of value 2, two coins of value 3, and one coin of value 7
2+3+3+7 = 15
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ranges>

void printmemo(std::vector<int> memo, int i){
    std::ranges::copy(memo,std::ostream_iterator<int>(std::cout,","));
    std::cout<<"==="<<i<<std::endl;
}
void initialise(std::vector<int> &coins, std::vector<int> &memo, int target){
    std::ranges::sort(coins);    
    memo[0]=1;
    int min=*std::ranges::min_element(coins);
    memo[min]=1;
}
void memoize(std::vector<int> &coins, std::vector<int> &memo, int target){
    int min=*std::ranges::min_element(coins);
    for (int i=min+1;i<memo.size();++i){
        for (const auto coin: coins){
            int count=0;
            if (coin>i)break;
            if (coin==i){
                count++;
            }
            else{
                memo[i]=memo[i-coin]+memo[coin];
            }
        }
        //printmemo(memo,i);
    }

}

int solve(std::vector<int> coins, int target){
    std::vector<int> memo(target+1,0);
    initialise(coins,memo,target);
    memoize(coins,memo,target);
    return memo[target];
}

int main(){
    std::vector<int> coins{2,3,7};
    int target=15;
    std::cout<<"Value="<<solve(coins,target)<<std::endl;
    return 0;
}