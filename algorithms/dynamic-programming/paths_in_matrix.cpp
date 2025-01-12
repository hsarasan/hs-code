/*
Paths in matrix (problem)
Given a matrix where a cell has the value of 1 if it's a wall and 0 if not, 
find the number of ways to go from the top-left cell to the bottom-right cell, 
knowing that it's not possible to pass from a wall and we can only go to the right or to the bottom
*/

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;

vector<vector<int>> matrix = {
    {0, 0, 1, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0}
    };

int getNoOfWays(const vector<vector<int>> & matrix){
    int m=matrix.size();
    int n=matrix[0].size();
    vector< vector<int> > dp(m, vector<int>(n,0));  
    dp[0][0]=1;
    for (int i=1; i<n; ++i){
        if (matrix[0][i-1]==0)
            dp[0][i]=dp[0][i-1];
    } 
    for (int i=1; i<m; ++i){
        if (matrix[i-1][0]==0)
            dp[i][0]=dp[i-1][0];
    }  
    for (int i=1;i<m;++i)
    for (int j=1;j<n;++j){
        if (matrix[i-1][j]==1 && matrix[i][j-1]==1) {
            dp[i][j]=0;
        }
        else if (matrix[i-1][j]==1){
            dp[i][j]=dp[i][j-1];
        }
        else if (matrix[i][j-1]==1){
            dp[i][j]=dp[i-1][j];
        }
        else {
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    for (int i=0;i<m;++i){
        copy(matrix[i].begin(), matrix[i].end(), ostream_iterator<int>(cout,","));
        cout<<endl;
    }
    cout<<"=================="<<endl;
    for (int i=0;i<m;++i){
        copy(dp[i].begin(), dp[i].end(), ostream_iterator<int>(cout,","));
        cout<<endl;
    }
    return dp[m-1][n-1];
}

int main(){
    int n=getNoOfWays(matrix);
    cout<<n<<endl;
    assert(n==7);
}