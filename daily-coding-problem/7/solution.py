def no_ways_to_decode(nums):
    n=len(nums)
    dp=[0]*(n+1)
    dp[0]=1
    dp[1]=1
    for i in range(1,n):
        if nums[i]==0:
            dp[i+1]=0
        elif nums[i]==1 or nums[i]==2:
            if (nums[i-1]==1 or nums[i-1]==2):
                dp[i+1]=dp[i-1]+dp[i]
            else:
                dp[i+1]=dp[i]
        elif 3<=nums[i]<=6:
            if (nums[i-1]==1 or nums[i-1]==2):
                dp[i+1]=dp[i-1]+dp[i]
            else:
                dp[i+1]=dp[i]
        else:
            if (nums[i-1]==1):
                dp[i+1]=dp[i-1]+dp[i]
            else:
                dp[i+1]=dp[i]
    return dp[n]


# Test cases
print(no_ways_to_decode([1, 1, 1]))  # Output: 3 (["AAA", "KA", "AK"])
print(no_ways_to_decode([2, 2, 6]))  # Output: 3 (["BBF", "VF", "BZ"])
print(no_ways_to_decode([1, 0]))     # Output: 1 (["J"])
print(no_ways_to_decode([2, 7]))     # Output: 1 (["BG"])
    