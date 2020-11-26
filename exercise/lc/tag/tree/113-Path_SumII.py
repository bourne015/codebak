
import sys
sys.path.append("../")
from create import *

class Solution:
    def pathSum1(self, root: TreeNode, sumt):
        stack, tmp, s = [], [], root.val
        node = root
        while node or stack:
            while node:
                stack.append(node)
                tmp.append(node.val)
                #s += node.val
                print("push:", node.val)
                node = node.left
            if stack:
                node = stack.pop()
                print("pop:", node.val)
                node = node.right
            if node == None:
                #s -= t
                ret.append(tmp)
                tmp.pop()
        return ret

    def dfs(self, root, sumt, sub, res):
        if not root:
            return
        if not root.left and not root.right and sumt == root.val:
            sub.append(root.val)
            res.append(sub)
        self.dfs(root.left, sumt-root.val, sub+[root.val], res)
        self.dfs(root.right, sumt-root.val, sub+[root.val], res)

    def pathSum(self, root: TreeNode, sumt):
        res = []
        self.dfs(root,sumt, [], res)
        return res
if __name__ == "__main__":
    a = [5,4,8,11,0, 13,4, 7,2,0,0,0,0,5,1]
    sumt = 22
    ret = []
    tree = Tree()
    t = tree.create_level(a)
    tree.print_tree(t)
    app = Solution()
    ret = app.pathSum1(t, sumt)
    print("maxdepth:",ret)
