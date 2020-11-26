
import sys
sys.path.append("../")
from create import *

class Solution:
    def houserb3(self, root: TreeNode):
        d = {}
        return self.dfs(root, d)

    def dfs(self, root, d):
        if not root:
            return 0
        if root in d:
            return d[root]
        val = 0
        if root.left:
            val += self.dfs(root.left.left, d) + self.dfs(root.left.right, d)
        if root.right:
            val += self.dfs(root.right.left, d) + self.dfs(root.right.right, d)
        val = max(val+root.val, self.dfs(root.left, d) + self.dfs(root.right, d))
        d[root] = val
        return val
if __name__ == "__main__":
    #a = [3,2,3,None,3,None,1]
    #a = [3,4,5,1,3,None,1]
    a = [4,1,None,2,None,None,None,3,None,None,None,None,None,None,None]
    tree = Tree()
    t = tree.create_level(a)
    tree.print_tree(t)
    app = Solution()
    ret = app.houserb3(t)
    print(ret)
