/*
Given the value and the weight of each one of n items, we want to maximize the value of items we take in our knapsack without exceeding its capacity k. You are asked to find the maximum total value that we can get without exceeding a total weight of k.
Note that each item can be took at most once.
Example:
input:
values = [20, 30, 15, 25, 10]
weights = [6, 13, 5, 10, 3]
k = 20
output: 55
explanation: The maximum total value that we can get is 55, by taking items 0, 3, and 4, their total weight doesn't exceed k
values[0]+values[3]+values[4] = 20+25+10 = 55
weights[0]+weights[3]+weights[4] = 6+10+3 = 19 <= 20
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;

void printmemo(vector<vector<int>> &memo){
    auto m = memo.size();
    auto n = memo[0].size();
    for (const auto row: memo){
        for (const auto & val : row){
            std::cout<<setw(3)<<val<<" ";
        }
        std::cout<<std::endl;
        
    }
    std::cout<<"====================="<<std::endl;
}
bool isViable(int w, int capacity){
    return w<=capacity;
}

std::tuple<int,int> getViableValueFromRow(vector<vector<int>> &memo, vector<vector<int>> &memoweight, vector<int> &weights, vector<int> & values, int row, int col, int weight){
    vector<int> fullRow = memo[row];
    vector<int> fullRowWeight = memoweight[row];
    for (int j=col;j>=0;--j){
        if (fullRowWeight[j]<=weight){
            return {fullRow[j],fullRowWeight[j]};
        }
    }
    return {-1,-1};
}

void memoize(vector<vector<int>> &memo, vector<vector<int>> &memoweight, vector<int> &weights, vector<int> & values, int capacity){
    auto m = memo.size();
    auto n = memo[0].size();
    for (int row=1;row<m;++row){
        std::cout<<"ROW="<<row<<std::endl;
        auto w = weights[row-1];
        auto v = values[row-1];
        for ( int col=1; col<n+1;++col){
            if (!isViable(w,col)){
                memo[row][col]=memo[row-1][col];
                memoweight[row][col]=memoweight[row-1][col];
                continue;
            }
            auto [prevViableValue,prevViableWeight] =getViableValueFromRow(memo, memoweight, weights, values, row-1, col, col-w);
            if (prevViableValue+v>memo[row-1][col]){
                memo[row][col]=prevViableValue+v;
                memoweight[row][col]=prevViableWeight+w;
            }
            else{
                memo[row][col]=memo[row-1][col];
                memoweight[row][col]=memoweight[row-1][col];
            }
        }
        printmemo(memo);
    }
}
int solve(vector<int> weights, vector<int>  values, int capacity){
    int m=weights.size()+1;
    int n=capacity+1;
    vector<vector<int>> memo(weights.size()+1, std::vector<int>(capacity+1,0));
    vector<vector<int>> memoweight(weights.size()+1, std::vector<int>(capacity+1,0));
    printmemo(memo);
    memoize(memo,memoweight, weights,values,capacity);
    return memo[m-1][n-1];
}
int main() {
    vector<int> values = {20, 30, 15, 25, 10};
    vector<int> weights = {6, 13, 5, 10, 3};
    int value = solve(weights, values, 20);
    std::cout<<"value="<<value<<std::endl;

    return 0;
}