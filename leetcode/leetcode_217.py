#contains duplicate
#Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

class Solution(object):
    def containsDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        S=set()
        for num in nums:
            if num in S:
                return True
            S.add(num)
        return False