#121. Best Time to Buy and Sell Stock
#You are given an array prices where prices[i] is the price of a given stock on the ith day.
#You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
#Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n=len(prices)
        if(n<2):
            return 0
        min_value_till_now=prices[0]
        profit=0
        for i in range(1,n):
            profit=max(profit, prices[i]-min_value_till_now)
            min_value_till_now=min(min_value_till_now,prices[i])
        return profit