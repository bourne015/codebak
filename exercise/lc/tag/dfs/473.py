
import sys
sys.path.append("../")
from create import *

class Solution:
    def makesquare(self, nums):
        if nums%4 != 0:
            return False
        edg_len = nums/4
        edgs = [0,0,0,0]

        return self.dfs(nums, edgs, edg_len, 0)

    def dfs(self, nums, edgs, edg_len, index):
        if not root:
            return None
        if not root.left and not root.right:
            tmp.append(root.val)
            return None
        for i in range(4):

        root.left = self.dfs(root.left, tmp)
        root.right = self.dfs(root.right, tmp)
        return root
if __name__ == "__main__":
    a = [1,1,2,2,2]
    app = Solution()
    ret = app.makesquare(a)
    print(ret)
