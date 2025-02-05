#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int lmax=0;
        int rmax=0;
        int left=0;
        int right=height.size()-1;
        int water=0;
        while(left<right){
            if (height[left]<height[right]){
                if (height[left]<lmax){
                    water+=lmax-height[left];
                }
                else{
                    lmax=height[left];
                }
                left++;
            }
            else{
                if (height[right]<rmax){
                    water+=rmax-height[right];
                }
                else{
                    rmax=height[right];
                }
                right--;
            }
        }
        return water;
    } 
};

int main(){
    Solution s;
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    assert(s.trap(height)==6);
    height={4,2,0,3,2,5};
    assert(s.trap(height)==9);
}