#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int stepsToCover(vector<vector<int>> &matrix, const pair<int,int>& start, const pair<int,int>& finish){

    vector<pair<int,int>> directions{{1,0},{-1,0},{0,1},{0,-1}};
    int m=matrix.size();
    int n=matrix[0].size();
    auto isValid=[&](int r, int c){
        return r>=0 && r<m && c>=0 && c<n && matrix[r][c]==0;
    };
    vector<vector<bool>> visited=vector<vector<bool>>(m,vector<bool>(n,false));
    vector<vector<int>> steps=vector<vector<int>>(m,vector<int>(n,-1));
    
    queue<pair<int,int>> Q;
    Q.push(start);
    steps[start.first][start.second]=0;
    visited[start.first][start.second]=true;
    while(!Q.empty()){
        auto p=Q.front();
        Q.pop();
        int r=p.first;
        int c=p.second;
        int steps_so_far=steps[r][c];
        for (const auto & direction: directions){
            int r_next=r+direction.first;
            int c_next=c+direction.second;
            if (isValid(r_next,c_next) && !visited[r_next][c_next]){
                steps[r_next][c_next]=steps_so_far+1;
                if (r_next==finish.first && c_next==finish.second)
                    return steps_so_far+1;
                Q.push({r_next,c_next});
                visited[r_next][c_next]=true;
            }    
        }
    }
    return -1;
}

int main(){

    vector<vector<int>> matrix= 
    {
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int steps=stepsToCover(matrix,make_pair<int,int>(3,0), make_pair<int,int>(0,0));
    cout<<"Steps = "<<steps<<endl;

}
