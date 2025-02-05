#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n=height.size();
        int i=0;
        int j=n-1;
        int maxArea=0;
        while(i<j){
            maxArea=max(maxArea, (j-i)*min(height[i],height[j]));
            if ( height[i] < height[j])
                i++;
            else 
                j--;
        }
        return maxArea;
    }
};


int main(){
    Solution s;
    vector<int> heights={1,8,6,2,5,4,8,3,7};
    assert(s.maxArea(heights)==49);
    heights={1,1};
    assert(s.maxArea(heights)==1);
}