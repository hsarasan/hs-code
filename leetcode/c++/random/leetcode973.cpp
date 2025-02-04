using namespace std;

struct compare_pairs{
bool operator()( const std::pair<int,int>  x, const std::pair<int,int>  y) const{
        return x.first*x.first + x.second*x.second < y.first*y.first + y.second*y.second;
    }
};
    

class Solution {
    std::multiset<std::pair<int,int>, compare_pairs> S;
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        std::vector<vector<int>> result;
        for ( const auto & point : points){
            S.insert({point[0],point[1]});
        }
        int count=0;
        for ( const auto & point : S){
            if (count==k) break;
            count++;
            result.push_back({point.first,point.second});
        }
        return result;
    }
};