class Solution:
    def getFactors(self, n):
        if n <= 1:
            return 1
        res = []
        self.dfs(res, n, 2, [])
        return res

    def dfs(self, res, n, index, tmp):
        if n == 1 and len(tmp) > 1:
            if tmp not in res:
                res.append(tmp)
        for i in range(index, n+1):
            t = n//i
            if t*i == n:
                self.dfs(res, t, i, tmp+[i])

if __name__ == "__main__":
    n = int(input())
    app = Solution()
    res = app.getFactors(n)
    print(res)
