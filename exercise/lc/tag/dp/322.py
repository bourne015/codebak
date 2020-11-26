class Solution(object):
    def coinChange(self, coins, amount):
        if not coins:
            return -1
        n = len(coins)
        dp = [amount+1]*(amount+1)
        dp[0] = 0
        for i in range(1,amount+1):
            for j in range(n):
                if i >= coins[j]:
                    dp[i] = min(dp[i], dp[i-coins[j]]+1)
        if dp[amount] == amount+1:
            return -1
        return dp[amount]

if __name__ == "__main__":
    a = [1, 2, 5]
    b = 10
    app = Solution()
    ret = app.coinChange(a, b)
    print(a, b)
    print(ret)
