def getMaxNonAdjacentSum(nums):
    n=len(nums)
    dp=[0]*(n+1)
    dp[1]=nums[0]
    dp[2]=max(nums[0],nums[1])
    max_val=-2**100
    for i in range(2,n):
        dp[i+1]=max(dp[i-1]+nums[i],dp[i])
    print(dp)
    return dp[n]

print(getMaxNonAdjacentSum([2, 4, 6, 2, 5]))
print(getMaxNonAdjacentSum([5,1,1,5]))