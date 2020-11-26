'''
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
'''

class Solution:
    def maxProfit(self, prices) -> int:
        ret = 0
        buy = prices[0]
        for x in prices[1:]:
            ret = max(x-buy, ret)
            buy = min(x, buy)

        return ret

    def maxProfit_dp(self, prices):
        res = [0 for x in prices]
        min_tmp = prices[0]
        for i, x in enumerate(prices[1:], 1):
            min_tmp = min(x, min_tmp)
            res[i] = max(res[i-1], x - min_tmp)
        return res[-1]

    def maxProfit_III(self, prices):
        f1 = f2 = [0 for x in prices]
        min_tmp = prices[0]
        n = len(prices)
        for i in range(n):
            for j in range(i+1):
                f1 = max(x)
            for k in range(i, n):

if __name__ == "__main__":
    a = [7,2,5,3,6,4]
    app = Solution()
    ret = app.maxProfit(a)
    print(a, '\n',ret)
    print(a, '\n', app.maxProfit_dp(a))
