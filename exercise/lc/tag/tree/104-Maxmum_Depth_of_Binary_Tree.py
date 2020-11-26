'''
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
Note: A leaf is a node with no children.
Example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.
'''
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

import sys
sys.path.append("../")
from create import *

class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if not root:
            return 0
        left = self.maxDepth(root.left)+1
        right = self.maxDepth(root.right)+1

        return max(left, right)
if __name__ == "__main__":
    a = [3, None, 20, None, None, 15, 7]
    tree = Tree()
    t = tree.create_level(a)
    tree.print_level(t)
    app = Solution()
    ret = app.maxDepth(t)
    print("maxdepth:",ret)


