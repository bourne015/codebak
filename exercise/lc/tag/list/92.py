import sys
sys.path.append("../")
from create import *

class Solution:
        def reverseBetween(self, head, m, n):
            dump = pre_m = ListNode(0)
            pre_m.next = head
            for i in range(m-1):
                pre_m = pre_m.next
            t1 = pre_m.next
            node = None
            for _ in range(n-m+1):
                t2 = t1
                t1 = t1.next
                t2.next = node
                node = t2
            pre_m.next.next = t1
            pre_m.next = node
            return dump.next
if __name__ == "__main__":
    nums = [1,2,3,4,5]
    m, n = 1, 4
    l = LinkList()
    h = l.create_list(nums)
    l.print_list(h)
    app = Solution()
    newh = app.reverseBetween(h, m, n)
    l.print_list(newh)
