'''
Given a non-negative integer rowIndex, generate the first rowIndex of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
'''
class Solution:
    def minimumtital(self, tri):
        res = tri[-1]
        return min(res)

if __name__ == "__main__":
    tri = [[2],
            [3,4],
            [5,6,7],
            [4,1,8,3]]
    for row in tri:
        print(row)
    app = Solution()
    ret = app.minimumtotal(tri)
    print(ret)

