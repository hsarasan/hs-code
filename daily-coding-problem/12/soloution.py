def getNumberOfWays(N,ways):
    dp=[0]*(N+1)
    dp[0]=1
    for i in range(1,N+1):
        no_of_ways=0
        for way in ways:
            if way<=i:
                no_of_ways+=dp[i-way]       
        dp[i]=no_of_ways
    return dp[N]

print(getNumberOfWays(4,[1,2]))