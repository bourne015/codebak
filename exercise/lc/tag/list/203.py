import sys
sys.path.append("../")
from create import *

class Solution:
        def delet(self, head, val):
            if not head:
                return None
            h = t = ListNode(0)
            while head:
                if head.val != val:
                    t.next = head
                    t = t.next
                head = head.next
                t.next = None

            return h.next
if __name__ == "__main__":
    nums1 = [1,1,2,3,4,5,5,6,7,8,9]
    l = LinkList()
    h1 = l.create_list(nums1)
    l.print_list(h1)
    val = int(input())
    app = Solution()
    newh = app.delet(h1, val)
    l.print_list(newh)
