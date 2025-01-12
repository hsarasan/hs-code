#70. Climbing Stairs
#You are climbing a staircase. It takes n steps to reach the top.
#Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

class Solution:
    def climbStairs(self, n: int) -> int:
        if (n==0): 
            return 1
        if (n==1):
            return 1
        if (n==2):
            return 2
        return self.climbStairs(n-1)+self.climbStairs(n-2)