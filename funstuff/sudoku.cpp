#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <set>

//A class that reads a 9x9 sudoku from a file and solves it
//file contains -1 for empty cells
class SudokuSolver{

    std::string fileName;
    std::vector<std::vector<int> >  sudokuMatrix;

    void readInputFile(){
        std::ifstream ifs(fileName);
        std::istream_iterator<std::string> begin(ifs);
        std::istream_iterator<std::string> finish;
        std::vector<std::string> v(begin,finish);
        for (const auto & str: v){
            std::stringstream ss(str);
            std::string num;
            std::vector<int> ip;
            while(std::getline(ss,num,',')){
                ip.emplace_back(std::stoi(num));
            }
            sudokuMatrix.emplace_back(ip);
        }
    }

    int numEmptyColumns(){
        int count{0};
        for (const auto & row: sudokuMatrix)
        for (const auto & cell: row)
            if(cell==-1) count++;
        return count;
    }

    void fixCells(){
            std::set<int> ref {1,2,3,4,5,6,7,8,9};
            std::vector<std::set<int>> rowRef(9);
            for (int i=0; i<9; ++i){
                std::set<int> temp;
                for (const auto & val : sudokuMatrix[i])
                    if (val!=-1) temp.insert(val);
                std::set_difference(ref.begin(), ref.end(), temp.begin(), temp.end(), std::inserter(rowRef[i], rowRef[i].begin()));
            }
            std::vector<std::set<int>> columnRef(9);
            for (int j=0;j<9;++j){
                std::set<int> temp;
                for (int i=0;i<9;++i)
                    if (sudokuMatrix[i][j]!=-1) temp.insert(sudokuMatrix[i][j]);
                std::set_difference(ref.begin(), ref.end(), temp.begin(), temp.end(), std::inserter(columnRef[j], columnRef[j].begin()));
            }

            for (int i=0; i<9;++i){
                for(int j=0; j<9; ++j){
                    std::vector<int> v;
                    if(sudokuMatrix[i][j]>0 ) continue;
                    std::set_intersection(rowRef[i].begin(), rowRef[i].end(), columnRef[j].begin(), columnRef[j].end(),std::back_inserter(v));
                    if (v.size()==1){
                        sudokuMatrix[i][j]=v.front();
                    }
                }
            }


        }
    public:
        SudokuSolver(const std::string & fileName):fileName(fileName){
            readInputFile();
        }
        void printSudokuMatrix(){
           for (const auto & vec : sudokuMatrix){
            std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout," "));
            std::cout<<std::endl;
            }
        }   
        void solve(){
            bool done = false;
            int prev=numEmptyColumns();
            while(!done){
                fixCells();
                int n=numEmptyColumns();
                done= n==prev || n==0;
            } 
        }

};
int main(int argc, char * argv[]) {
        if (argc!=2){
            std::cout<<"Usage "<<argv[0]<<" [filename]"<<std::endl;
            return 1;
        }
       SudokuSolver sudoku(argv[1]);
       sudoku.solve();
       sudoku.printSudokuMatrix();
       return 0;
}