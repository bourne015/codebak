'''
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.
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
    def minDepth(self, root: TreeNode) -> int:
        if not root:
            return 0
        if not root.left and root.right:
            return self.minDepth(root.right)+1
        if not root.right and root.left:
            self.minDepth(root.left)+1
        left = self.minDepth(root.left)+1
        right = self.minDepth(root.right)+1
        return min(left, right)
if __name__ == "__main__":
    a = [3, None, 20, None, None, 15, 7]
    print(a)
    tree = Tree()
    t = tree.create_level(a)
    tree.print_tree(t)
    app = Solution()
    ret = app.minDepth(t)
    print("min depth:", ret)
