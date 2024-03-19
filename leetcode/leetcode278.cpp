class Solution {
public:
    int firstBadVersion(int n) {
        long left=1;
        long right=n;
        long mid;
        if (n==1) return 1;
        int earliest_found=0;
        while(left<=right){
            mid=(left+right)/2;
            if (isBadVersion(mid) )
            {
                earliest_found=mid;
            }
            if (!isBadVersion(mid)){
                left=mid+1;
            }
            else{
                right=mid-1;
            }

        }
        return earliest_found;
    }
};