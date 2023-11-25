/*
You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        std::vector<int> sortedArray;
        auto checkDone = [&](int idx1, int idx2)->bool {
            return idx1==m || idx2==n;
        };
        bool done = checkDone(0,0);
        int nums1_idx{0};
        int nums2_idx{0};
        while (!done)
        {
            if (nums1[nums1_idx]< nums2[nums2_idx])
            {
                sortedArray.push_back(nums1[nums1_idx++]);
            }
            else
            {
                sortedArray.push_back(nums2[nums2_idx++]);
            }
            done = checkDone(nums1_idx, nums2_idx);
        }
        if (nums1_idx==m)
        {
            std::copy(nums2.begin() + nums2_idx, nums2.end(), std::back_inserter(sortedArray));
            nums1 = std::move(sortedArray);
        }
        else
        {
            std::copy(nums1.begin() + nums1_idx, nums1.begin() + m, std::back_inserter(sortedArray));
            nums1 = std::move(sortedArray);
        }
        
    }
};

class Solution2 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        int nums1_logical_end = m;
        std::for_each(nums2.begin(), nums2.end(),
        [&](int item)
        {
            auto iter = std::upper_bound(nums1.begin(), nums1.begin()+nums1_logical_end, item);
            if (iter!=nums1.begin() + nums1_logical_end)
            {
                nums1.insert(iter,item);
                nums1.pop_back();
                nums1_logical_end++;
            }
            else
            {
                nums1[nums1_logical_end++]=item;
            }
        }
        );
    }

};

class BestSolution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        int j=n-1;
        int i=m-1;
        int curr_pos=m+n-1;
        while (j>=0)
        {
            if (i>=0 && nums1[i] > nums2[j])
            {
                nums1[curr_pos--]=nums1[i--];
            }
            else
            {
                nums1[curr_pos--]=nums2[j--];
            }
        }
    }
};

int main() {

    std::vector<int> nums1{0};
    std::vector<int> nums2{1};
    BestSolution s3;
    s3.merge(nums1, 0, nums2,1 );
    std::copy(nums1.begin(), nums1.end(), std::ostream_iterator<int>(std::cout, " "));
}