
class Solution:
    def minimumtital(self, k, n):
        res = []
        self.dfs(res, k, n, 1, [])
        return res
    def dfs(self, res, k, n, index, tmp):
        if n == 0 and k == 0:
            res.append(tmp)
            tmp = []
        elif n < 0 or k < 0:
            return
        for i in range(index, 10):
            self.dfs(res, k-1, n-i, i+1, tmp+[i])

if __name__ == "__main__":
    k, n =  [int(x) for x in input().split()]
    app = Solution()
    ret = app.minimumtital(k, n)
    print(k, n)
    print(ret)

