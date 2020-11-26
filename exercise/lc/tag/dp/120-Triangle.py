'''
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:

Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
'''
class Solution(object):
    def minimumTotal(self, triangle):
        """
        :type triangle: List[List[int]]
        :rtype: int
        """
        f = [triangle[0][0] for x in range(len(triangle[-1]))]
        for i in range(1,len(triangle)):
            for j in range(i,-1,-1):
                if j == 0:
                    f[j] = f[j] + triangle[i][j]
                elif j == i:
                    f[j] = f[j-1] + triangle[i][j]
                else:
                    f[j] = min(f[j], f[j-1]) + triangle[i][j]
            print(f)
        return min(f)


if __name__ == "__main__":
    a = [[2],[3,4],[6,5,7],[4,1,8,3]]
    app = Solution()
    ret = app.minimumTotal(a)
    print(a)
    print(ret)
