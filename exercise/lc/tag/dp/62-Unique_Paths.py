'''
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
'''

class Solution:
        def uniquePaths(self, m: int, n: int) -> int:
            f = [[1 for i in range(m)] for j in range(n)]
            for i in range(1, n):
                for j in range(1, m):
                    f[i][j] = f[i-1][j]+f[i][j-1]
            return f[-1][-1]
if __name__ == "__main__":
    m, n = 7, 3
    app = Solution()
    ret = app.uniquePaths(m, n)
    print(m, n)
    print(ret)
