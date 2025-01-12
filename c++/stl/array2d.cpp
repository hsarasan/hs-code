#include <bits/stdc++.h>

using namespace std;

template <typename T, int row, int column>
class Array2D{
    vector< vector<T> > v;
    public:
        Array2D(){
            for (int i=0;i<row;++i){
                v.push_back(vector<T>(column,0));
            }
            cout<<"Size = "<<v.size()<<endl;
        }
        vector<T> & operator[](int idx){
            return v[idx];
        }
        string to_string(){
            stringstream ss;
            for (int i=0;i<row;++i)
            for (int j=0;j<column;++j){
                ss<<v[i][j]<<" ";
            }
            return ss.str();
        }

        friend ostream & operator<<(ostream & o, Array2D & obj){
            o<<obj.to_string();
            return o;
        }
};


int main(){
    Array2D<int, 3,3> D2Array;
    D2Array[0][1]=9;
    D2Array[1][1]=12;
    cout<<D2Array<<endl;
    return 0;
}