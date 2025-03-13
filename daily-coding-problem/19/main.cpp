#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


using namespace std;

void print(vector< vector<int>> & matrix){
    for (int i=0; i<matrix.size(); ++i){
        copy(matrix[i].begin(), matrix[i].end(), ostream_iterator<int>(cout,","));
        cout<<endl;
    }
}

int getMinAfterIgnore(vector<int> v,int ignore_idx){
    v[ignore_idx]=INT_MAX;
    return *min_element(v.begin(),v.end());
}

int getMinCost(vector< vector<int>> &costs){
    int n=costs.size();
    int k=costs[0].size();
    vector< vector<int>> dp(n, vector<int>(k, 0));
    for (int i=0;i<k;++i) dp[0][i]=costs[0][i];
    for (int i=1; i<n; ++i){
        for (int j=0;j<k;++j){
            int cost_till_now=getMinAfterIgnore(dp[i-1],k);   
            dp[i][j]=cost_till_now+costs[i][j];
        }
    }
    print(dp);
    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

int main(){

    vector< vector<int>> costs = {
        {17, 2, 17}, 
        {16, 16, 5},  
        {14, 3, 19}   
    };
    cout<<getMinCost(costs)<<endl;
    return 0;
}