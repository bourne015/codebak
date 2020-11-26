'''
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
'''

class Solution:
        def uniquePaths(self, a) -> int:
            n, m = len(a), len(a[0])
            f = [[1 for i in range(m)] for j in range(n)]
            t = 0
            for i in range(m):
                t += a[0][i]
                if t>0:
                    f[0][i] = 0
            t = 0
            for i in range(n):
                t += a[i][0]
                if t>0:
                    f[i][0] = 0
            for i in range(1, n):
                for j in range(1, m):
                    if a[i][j] == 1:
                        f[i][j] = 0
                    elif a[i-1][j] == 1 and a[i][j-1] == 0:
                        f[i][j] = f[i][j-1]
                    elif a[i-1][j] == 0 and a[i][j-1] == 1:
                        f[i][j] = f[i-1][j]
                    elif a[i-1][j] == 1 and a[i][j-1] == 1:
                        f[i][j] = 0
                    else:
                        f[i][j] = f[i-1][j]+f[i][j-1]
            return f[-1][-1]
if __name__ == "__main__":
    a = [[0, 0], [0, 1]]
    app = Solution()
    ret = app.uniquePaths(a)
    print(a)
    print(ret)
