#448. Find All Numbers Disappeared in an Array

#Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.:w

class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        n=len(nums)
        missing=set(range(1,n+1))
        for num in nums:
            missing.discard(num)
        return list(missing)