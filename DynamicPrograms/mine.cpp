/*
Given a mine of n rows and m columns where mine{i}{j} represents the amount of gold that is present there, we want to enter from the top of the mine and take as much gold as possible when exiting from the bottom, knowing that we can only move to the bottom, to the bottom-left, or to the bottom-right. We can exit from anywhere from the last row.
Example:
input:
mine = {
   {3, 2, 12, 15, 10},
   {6, 19, 7, 11, 17},
   {8, 5, 12, 32, 21},
   {3, 20, 2, 9, 7}
}
output: 73

*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

void printMemo(std::vector<std::vector<int>> &memo){
    std::cout<<"=================================="<<std::endl;
    for (const auto row: memo){
        for ( const auto val: row){
            std::cout<<std::setw(3)<<val<<",";
        }
        std::cout<<std::endl;
    }
}

int solve (std::vector<std::vector<int>> &memo){
    return *std::max_element(memo[0].begin(), memo[0].end());
}
void memoise(const std::vector<std::vector<int>> &mine,std::vector<std::vector<int>> &memo){
    int rowsize=mine.size();
    int colsize=mine[0].size();
    int leftBottomValue;
    int rightBottomValue;
    int bottomValue;
    for (int i=rowsize-2;i>=0;--i){
    for (int j=0;j<colsize;++j){
        leftBottomValue=j==0?0:memo[i+1][j-1]+ mine[i][j];
        rightBottomValue=j==colsize-1?0:memo[i+1][j+1]+mine[i][j];
        bottomValue=memo[i+1][j]+mine[i][j];
        memo[i][j]=std::max(bottomValue, std::max(leftBottomValue,rightBottomValue));
        //std::cout<<"bv="<<bottomValue<<" lbv="<<leftBottomValue<<" rbv="<<rightBottomValue<<" val="<<memo[i][j]<<std::endl;
    }
    }
}

void initialconditions(const std::vector<std::vector<int>> &mine, std::vector<std::vector<int>> &memo)
{
    int rowsize=mine.size();
    int colsize=mine[0].size();
    for ( int i=0; i<colsize;++i){
        memo[rowsize-1][i]=mine[rowsize-1][i];
    }
}

int solution(const std::vector<std::vector<int>> &mine){
    int rowsize=mine.size();
    int colsize=mine[0].size();
    std::vector<std::vector<int>> memo(rowsize,std::vector<int>(colsize,0));
    initialconditions(mine, memo);
    //printMemo(memo);
    memoise(mine,memo);
    //printMemo(memo);
    return solve(memo);
    
}

int main(){

    std::vector<std::vector<int>> mine;
    mine = {
    {3, 2, 12, 15, 10},
    {6, 19, 7, 11, 17},
    {8, 5, 12, 32, 21},
    {3, 20, 2, 9, 7} 
    };
    int val=solution(mine);
    std::cout<<"Max="<<val<<std::endl;
    return 0;
}