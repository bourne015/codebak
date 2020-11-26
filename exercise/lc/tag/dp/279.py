class Solution(object):
    #DFS
    def numSquares(self, n):
        if n <= 2:
            return n
        res = []
        self.dfs(n, res, [])
        return min(len(a) for a in res)

    def dfs(self, sub, res, t):
        if sub < 0:
            return
        if sub == 0:
            res.append(t)
        for i in range(1, sub+1):
            if i*i <= sub:
                self.dfs(sub-i*i, res, t+[i*i])
            else:
                break

    #DP
    def numSquares2(self, n):
        if n <= 2:
            return n
        dp = [n]*(n+1)
        dp[0] = 0
        for i in range(1, n+1):
            j = 1
            while j*j <= i:
                dp[i] = min(dp[i], dp[i-j*j]+1)
                j += 1
        return dp[n]

if __name__ == "__main__":
    a = int(input())
    app = Solution()
    ret = app.numSquares2(a)
    print(a)
    print(ret)
