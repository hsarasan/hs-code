#include <iostream>
#include <vector>
#include <unordered_set>


class Solution {
    bool checkMatrix(std::unordered_set<char> &matrix, char mat){
        if(matrix.count(mat)) return true;
        matrix.insert(mat);
        return false;
    }
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::vector<std::unordered_set<char>> rows{9,std::unordered_set<char>{}};
        std::vector<std::unordered_set<char>> cols{9,std::unordered_set<char>{}};
        std::vector<std::unordered_set<char>> matrix{9,std::unordered_set<char>{}};
        for (int row=0;row<9;++row){
            for (int col=0; col<9; ++col){
                int mat = col/3 + 3*(row/3);
                char c = board[row][col];
                if(c=='.') continue;
                auto b1 = checkMatrix(rows[row],c);
                auto b2 = checkMatrix(cols[col],c);
                auto b3 = checkMatrix(matrix[mat],c);
                if (b1||b2||b3)
                    return false;
            }
        }
        return true;
    }
};

int main(){
    return 0;
}

