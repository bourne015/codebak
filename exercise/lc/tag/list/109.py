import sys
sys.path.append("../")
from create import *

class Solution:
        def List2BST(self, head):
            if not head:
                return None
            if not head.next:
                return TreeNode(head.val)
            slow,fast = head, head.next.next
            while fast and fast.next:
                fast = fast.next.next
                slow = slow.next
            node = slow.next
            root = TreeNode(node.val)
            slow.next = None
            root.left = self.List2BST(head)
            root.right = self.List2BST(node.next)
            return root

if __name__ == "__main__":
    nums1 = [1,2,3,4,5,6,7,8,9, 10]

    l = LinkList()
    h1 = l.create_list(nums1)
    l.print_list(h1)

    app = Solution()
    t = app.List2BST(h1)
    tree = Tree()
    tree.print_tree(t)
