/*
The problem of "building  N houses with K paints" is a common coding interview problem. It involves optimizing the cost of painting 
N houses such that no two adjacent houses have the same color, while minimizing the total cost.

Problem Statement
Input:
N: Number of houses.
K: Number of available colors.
A 2D array cost of size 𝑁 × 𝐾 where cost{i}{j} represents the cost of painting house i with color j.
Output:
The minimum cost to paint all houses under the given constraints.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int min_row_value(vector<vector<int>> &cost, int row, int ignore_cell){

    int min_value{INT_MAX};
    for (int i=0;i<cost[row].size();++i){
        if (i!=ignore_cell){
            min_value=min(min_value,cost[row][i]);
        }
    }
    return min_value;
}

int min_cost(vector<vector<int>> &cost){
    int N=cost.size();
    int k=cost[0].size();
    vector<vector<int>> dp(N,vector<int>(k,0));
    for (int i=0;i<k;++i) dp[0][i]=cost[0][i];
    for (int i=1;i<N;++i)
    for (int j=0;j<k;++j){
       dp[i][j] = cost[i][j] + min_row_value(dp, i - 1, j);
        
    }
    
    return *min_element(dp[N-1].begin(), dp[N-1].end());
}

int main(){
    vector<vector<int>> cost = {
        {1, 5, 3},
        {2, 9, 4}
    };
    int n=min_cost(cost);
    cout<<n<<endl;
    return 0;
}