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
    def getRow(self, rowIndex: int):
        res = []
        for i in range(0, rowIndex+1):
            tmp = []
            for j in range(i+1):
                if j == 0 or j == i:
                    tmp.append(1)
                else:
                    tmp.append(res[i-1][j-1] + res[i-1][j])
            res.append(tmp)
        return res

if __name__ == "__main__":
    level = int(input('input level:'))
    app = Solution()
    res = app.getRow(level)
    for row in res:
        print(row)

