#include "scoped_timer.hpp"

using namespace std;

int main(){
    const int N = 100000;
    const int M = 100000;
    auto result=0;
    vector<vector<int>> matrix(N,vector<int>(M,1));
    int count;
    {
        scoped_timer t("Matrix Operation");
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                result+=matrix[i][j];
            }
        }       
    }
    {
        scoped_timer t("Matrix Operation column major style");
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                result+=matrix[j][i];
            }
        }       
    }

    return 0;
}