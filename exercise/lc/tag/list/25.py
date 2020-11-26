import sys
sys.path.append("../")
from create import *

class Solution:
        def reversekgroup(self, head, k):
            t, l = head, 0
            while t:
                t = t.next
                l += 1
            dum = p = ListNode(0)
            p.next = head
            for _ in range(l//k):
                tmp = None
                for _ in range(k):
                    node = head
                    head = head.next
                    node.next = tmp
                    tmp = node
                p1 = p.next
                p.next = tmp
                p1.next = head
                p = p1
            return dum.next

if __name__ == "__main__":
    nums1, k = [1,2,3,4,5,6,7,8,9, 10], 3

    l = LinkList()
    h1 = l.create_list(nums1)
    l.print_list(h1)
    app = Solution()
    newh = app.reversekgroup(h1, k)
    l.print_list(newh)
