/*
1065. Index Pairs of a String
Given a string text and an array of strings words, 
return an array of all index pairs [i, j] so that the substring text[i...j] is in words.
Return the pairs [i, j] in sorted order (i.e., sort them by their first coordinate, 
and in case of ties sort them by their second coordinate).
*/
class Solution {
public:
    struct Sorter{
        bool operator()(const vector<int> &a, const vector<int> &b )const{
            return a[0]<b[0] || (a[0]==b[0] && a[1]<b[1]);
        }
    };
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        vector<vector<int>> result;
        for (const auto & word: words){
            int start=0;
            bool done{false};
            while(!done){
                size_t found_at=text.find(word,start);
                if (found_at!=string::npos){
                    int pos=found_at;
                    int pos_end=pos+word.size()-1;
                    result.push_back({pos,pos_end});
                    start=found_at+1;
                }
                else{
                    done=true;
                }
            }
        } 
        sort(result.begin(), result.end(), Sorter());
        return result;  
    }
};