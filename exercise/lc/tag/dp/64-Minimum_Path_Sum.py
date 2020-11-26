'''
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
'''
class Solution(object):
    def minPathSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n, m = len(grid), len(grid[0])
        f = [[0 for i in range(m)] for j in range(n)]
        f[0][0] = grid[0][0]
        for i in range(1, n):
            f[i][0] = f[i-1][0] + grid[i][0]
        for j in range(1, m):
            f[0][j] = f[0][j-1] + grid[0][j]
        for i in range(1, n):
            for j in range(1, m):
                f[i][j] = min(f[i-1][j], f[i][j-1])+grid[i][j]
        return f[-1][-1]

if __name__ == "__main__":
    a = [[1,3,1],[1,5,1],[4,2,1]]
    app = Solution()
    ret = app.minPathSum(a)
    print(a)
    print(ret)
