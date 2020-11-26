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
        res = [1]*(rowIndex+1)
        for i in range(0, rowIndex+1):
            for j in range(i, -1, -1):
                if j == 0 or j == i:
                    res[j] = 1
                else:
                    res[j] = res[j-1] + res[j]
        return res

if __name__ == "__main__":
    app = Solution()
    ret = app.getRow(4)
    print(ret)

