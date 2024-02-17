/*
Given two strings word1 and word2, calculate their edit distance.
The edit distance in this problem is defined as the minimum number of insertions, deletions, and substitutions of characters to go from word1 to word2.



Example:

input:
word1 = "inside"
word2 = "index"

output: 3

explanation: To go from "inside" to "index", we can delete the character 's', delete the second character 'i', and insert a character 'x' at the end, in total we need 3 operations
"inside" -> "inide" -> "inde" -> "index"


*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>

/* ////////////////////////////// 

d[i][j] - is the distance between first i characters of s1 and first j characters of s2
if s[i]==s[j] d[i][j]=d[i-1][j-1]
else d[i][j]=1+std::min(d[i-1][j-1],d[i-1][j],d[i][j-1])

Limiting conditions
s[0][i]=i
s[j][0]=j
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void printMemo(const std::vector<std::vector<int>>& memo){
    for (const auto & row: memo)
    {
        for (const auto & val: row){
            std::cout<<std::setw(3)<<val<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void initialise(std::vector<std::vector<int>> &memo){
    auto & row = memo[0];
    std::iota(row.begin(), row.end(),0);
    int m=memo.size();
    for (int i=0;i<m;++i)
    {
        memo[i][0]=i;
    }
}

int solve(std::string s1, std::string s2){
    int m=s1.size();
    int n=s2.size();
    std::vector<std::vector<int>> memo(m+1,std::vector<int>(n+1,0));
    initialise(memo);
    for (int i=1;i<m+1;++i)
    for (int j=1;j<n+1;++j)
    {
        if (s1[i]==s2[j]){
            memo[i][j]=memo[i-1][j-1];
        }
        else {
            int above = memo[i-1][j];
            int left = memo[i][j-1];
            int diag = memo[i-1][j-1];
            memo[i][j]=1+std::min( above, std::min(left,diag));
        }
    }
    printMemo(memo);
    return memo[m][n];
}

int main(){
    std::string word1 = "inside";
    std::string word2 = "index";
    int val = solve(word1,word2);
    std::cout<<"Val="<<val<<std::endl;
    return 0;
}