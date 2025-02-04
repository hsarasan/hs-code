class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::vector<vector<int>> results;
        std::sort(begin(intervals),end(intervals));
        int N = intervals.size();
        std::vector<int> flat_vector;
        flat_vector.push_back(intervals[0][0]);
        flat_vector.push_back(intervals[0][1]);
        int i=1;
        while(i<N){
            int fN = flat_vector.size();
            int a = flat_vector[fN-2];
            int b = flat_vector[fN-1];
            int c = intervals[i][0];
            int d = intervals[i][1];
            if (c<=b && d>=b) {
                flat_vector.pop_back();
                flat_vector.push_back(d);
            }
            else if (c<b && d<b){
                //do nothing
            }
            else {
                flat_vector.push_back(c);
                flat_vector.push_back(d);
            }



            i=i+1;
        }


        N = flat_vector.size();
        i=0;
        while(i<N){
            vector<int> result{flat_vector[i], flat_vector[i+1]};
            i=i+2;
            results.push_back(result);
        }
        return results;
    }
};