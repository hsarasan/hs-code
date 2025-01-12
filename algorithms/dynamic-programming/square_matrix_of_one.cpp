/*
Given a matrix of ones and zeros, find the area of the greatest square submatrix full of ones.
A square matrix is a matrix whose the number of rows is equal to the number of columns.

Example:
intput:
matrix = {
   {0, 0, 1, 1, 1, 0},
   {1, 0, 1, 1, 1, 1},
   {0, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 0, 1},
   {0, 1, 0, 1, 1, 1}
}
output: 9
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int getMaxOneMatrixArea(vector<vector<int>> matrix ){

    int m=matrix.size();
    int n=matrix[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    int max_side=0;
    for (int i=0;i<n;++i){
        dp[0][i]=matrix[0][i];
    }
    for (int i=0; i<m; ++i){
        dp[i][0]=matrix[i][0];
    }
;
    for (int i=1; i<m; ++i)
    for (int j=1; j<n; ++j){
        if (matrix[i][j]==1){
            dp[i][j]=1+min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));
        }
    }
    for (int i=0;i<m;++i)
        max_side=max(max_side, *max_element(dp[i].begin(), dp[i].end()));
    return max_side*max_side;
}
int main(){
    vector<vector<int>> matrix = {
     {0, 0, 1, 1, 1, 0},
     {1, 0, 1, 1, 1, 1},
     {0, 1, 1, 1, 1, 0},
     {1, 1, 1, 1, 0, 1},
     {0, 1, 0, 1, 1, 1}
    };
    int n=getMaxOneMatrixArea(matrix);
    cout<<n<<endl;
    matrix = {
     {0, 0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 1, 0},
     {1, 1, 1, 1, 0, 1},
     {0, 1, 0, 1, 1, 1}
    };
    n=getMaxOneMatrixArea(matrix);
    cout<<n<<endl;
    matrix = {
     {0, 0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0}
    };
    n=getMaxOneMatrixArea(matrix);
    cout<<n<<endl;
    matrix = {
     {0}
    };
    n=getMaxOneMatrixArea(matrix);
    cout<<n<<endl;
    return 0;
}
