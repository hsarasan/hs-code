
/*
Given a matrix where a cell has the value of 1 if it 's a wall and 0 if not, find the number of ways to go from the top-left cell to the bottom-right cell, knowing that it' s not possible to pass from a wall and we can only go to the right or to the bottom

input:
matrix = [
    [0, 0, 1, 0, 1],
    [0, 0, 0, 0, 1],
    [0, 0, 1, 0, 0],
    [1, 0, 0, 0, 0]
]

output: 7
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::map<std::pair<int,int>,int> table;

void printLookupTable() {
    for ( const auto & [k,v]: table){
        std::cout<<k.first<<","<<k.second<<"=>"<<v<<std::endl;
    }
}
int lookup(int i,int j){
    if (table.count({i,j})>0)
        return table[{i,j}];
    return -1;
}
void store(int i, int j, int value){
    table[{i,j}]=value;
}

void process(std::vector<std::vector<int>> &matrix, int i, int j){
    if (matrix[i][j]==1) return;
    if (i==0 && j==0)
    {
        store(0,0,0);
    } 
    else  if (i==0) {
        int x = lookup(i,j-1);
        if (x>=0) store(i,j,1);
    }
    else  if (j==0) {
        int x = lookup(i-1,j);
        if (x>=0) store(i,j,1);
    }
    else {
        int x=lookup(i-1,j);
        int y=lookup(i,j-1);
        if (x>=0 && y>=0) store(i,j,x+y);
        else if  (x>0) store(i,j,x);
        else store(i,j,y);

    }
}
void initialise(std::vector<std::vector<int>> &matrix){
    process(matrix,0,0);
    int rowN=matrix.size();
    int colN=matrix[0].size();
    for ( int i=0; i<rowN; ++i) 
        process(matrix,i,0);
    for (int j=0; j<colN; ++j){
        process(matrix,0,j);
    }

}

int solution(std::vector<std::vector<int>> &matrix){
    int rowN=matrix.size();
    int colN=matrix[0].size();
    initialise(matrix);
    for ( int i=0; i<rowN; ++i)
    for (int j=0; j<colN; ++j)
    {
        process(matrix,i,j);
    }
    int final_value=lookup(rowN-1,colN-1);
    return final_value;
}


int main() {
    std::vector<std::vector<int>> matrix = {
      {0, 0, 1, 0, 1},
      {0, 0, 0, 0, 1},
      {0, 0, 1, 0, 0},
      {1, 0, 0, 0, 0}
    };
    int v=solution(matrix);
    printLookupTable();
    std::cout<<v<<std::endl;
    return 0;
}