import sys
sys.path.append("../")
from create import *

class Solution:
        def reverse(self, head):
            if not head or not head.next:
                return head
            t = None
            while head:
                node = head
                head = head.next
                node.next = t
                t = node
            return t
if __name__ == "__main__":
    nums = [1,2,3,4,5]
    m, n = 2, 4
    l = LinkList()
    h = l.create_list(nums)
    l.print_list(h)
    app = Solution()
    newh = app.reverse(h)
    l.print_list(newh)
