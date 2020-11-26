import sys
sys.path.append("../")
from create import *

class Solution:
        def odd_even(self, head):
            if not head or not head.next:
                return head
            t = ListNode(0)
            h=t
            i, odd, even = 1, head, head.next
            while odd:
                t.next = odd
                t = t.next
                if odd.next:
                    odd = odd.next.next
            return h.next
if __name__ == "__main__":
    nums1 = [1,2,3,4,5,6,7,8]
    #nums1 = [1]
    l = LinkList()
    h1 = l.create_list(nums1)
    l.print_list(h1)
    app = Solution()
    newh = app.odd_even(h1)
    l.print_list(newh)
