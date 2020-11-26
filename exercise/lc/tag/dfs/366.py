
import sys
sys.path.append("../")
from create import *

class Solution:
    def find_leaves(self, root: TreeNode):
        res = []
        while root:
            tmp = []
            root = self.dfs(root, tmp)
            res.append(tmp)

        return res

    def dfs(self, root, tmp):
        if not root:
            return None
        if not root.left and not root.right:
            tmp.append(root.val)
            return None

        root.left = self.dfs(root.left, tmp)
        root.right = self.dfs(root.right, tmp)
        return root
if __name__ == "__main__":
    #a = [3,2,3,None,3,None,1]
    #a = [3,4,5,1,3,None,1]
    a = [1,2,3,4,5,None, None]
    res = []
    tree = Tree()
    t = tree.create_level(a)
    tree.print_tree(t)
    app = Solution()
    ret = app.find_leaves(t)
    print(ret)
