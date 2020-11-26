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
    def list(self, root: TreeNode):
        res, stack = [], [root]
        last = TreeNode(-1)
        while stack:
            t = stack.pop()
            if t:
                last.right = t
                last.left = None
                stack.append(t.right)
                stack.append(t.left)
                last = t

if __name__ == "__main__":
    a = [1, 2, 5, 3, 4, None, 6]
    tree = Tree()
    t = tree.create_level(a)
    tree.print_level(t)
    app = Solution()
    app.list(t)

    while t:
        print(t.val)
        t = t.right


