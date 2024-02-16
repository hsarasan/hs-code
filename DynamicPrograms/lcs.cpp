/*Given two strings s1 and s2, find the length of their longest common subsequence.

A subsequence of a string s is a subset of its characters that are not necessarily adjacent but have to be in the right order.

Example:

input:
s1 = "abdacbab"
s2 = "acebfca"

output: 4
explanation: A possible longest common subsequence of s1 and s2 is "abca" */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void printMemo(const std::vector<std::vector<int>> &memo){
    std::cout<<"================================="<<std::endl;
    for (const auto & row: memo){
        for ( const auto value: row){
            std::cout<<value<<" ";
        }
        std::cout<<std::endl;
    }
}
void initialise(std::vector<std::vector<int>> &memo){
    auto &rowzero=memo[0];
    int mx=*std::max_element(rowzero.begin(),rowzero.end());
    if (mx==1) std::fill(rowzero.begin(), rowzero.end(),1);
    mx=0;
    for (int i=0;i<memo[0].size();++i){
        if (memo[i][0]==1) {
            mx=1;
            break;
        }
    }
    for (int i=0;i<memo.size();++i){
        memo[i][0]=mx;
    }   
}

//Not  implemented
std::string getlcsString(std::vector<std::vector<int>> &memo,std::string s1, std::string s2){
    int m=s1.size();
    int n=s2.size();
    int i=m-1;
    int j=n-1;
    std::string lcs;

   return lcs;
}
int lcs(std::string s1, std::string s2){
    int m=s1.size();
    int n=s2.size();
    std::vector<std::vector<int>> memo(m,std::vector<int>(n,0));
    for (int i=0;i<m;++i)
    for (int j=0;j<n;++j)
    {
        
        if (s1[i]==s2[j]) memo[i][j]=1;
        //std::cout<<i<<","<<j<<"=>"<<s1[i]<<","<<s2[j]<<"=>"<<memo[i][j]<<std::endl;
    }
    //std::cout<<std::endl;
    //printMemo(memo);
    initialise(memo);
    //printMemo(memo);
    for (int i=1;i<m;++i)
    for (int j=1;j<n;++j){
        memo[i][j]=std::max(memo[i-1][j], memo[i][j-1]) + memo[i][j];
    }
    //printMemo(memo);
    //getlcsString(memo,s1,s2);
    return memo[m-1][n-1];
}

int main() {
    std::string s1, s2;
    s1 = "abdacbab";
    s2 = "acebfca";
    auto lcs_v=lcs(s1,s2);
    std::cout<<"LCS="<<lcs_v<<std::endl;
    return 0;
}