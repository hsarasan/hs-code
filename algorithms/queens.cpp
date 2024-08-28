#include <iostream>
#include <vector>

std::vector< std::vector<int> > chess_table;

int N;

void printChessTable(){
    for (const auto & row: chess_table){
        for (const auto  & value : row)
            std::cout<<value<<",";
        std::cout<<std::endl;
    }
}
void initialise(){
    for (int i=0;i<N;++i) {
        std::vector<int> v(N,0);
        chess_table.push_back(v);
    }
}
bool isViable(int i, int j){
    for (int col=0;col<j;++col){
        if (chess_table[i][col]==1) return false;
    }
    auto row=i;
    int count=1;
    for (int col=j-1;col>=0;--col){
        if (row-count>=0 && chess_table[row-count][col]==1) return false;
        if (row+count<N && chess_table[row+count][col]==1) return false;
        count++;
    }
    
    return true;
}
bool solve(int col){
    if (col==N) return true;
    for (int row=0;row<N;++row){
        bool viable=isViable(row,col);
        if (viable){
            chess_table[row][col]=1;
            auto next=col+1;
            bool success=solve(next);
            if (!success) chess_table[row][col]=0;
            if (success) return success;
        }
    }
    return false;
    
}

void queens(int n){
    N=n;
    initialise();
    auto ret=solve(0);
    if (!ret) std::cout<<"No solution "<<std::endl;
    if (ret) printChessTable();
}

int main(){
    queens(8);
    return 0;
}