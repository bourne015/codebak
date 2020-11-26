import sys
sys.path.append("../")
from create import *

class Solution:
        def reverse(self, head):
            if not head or not head.next:
                return head
            newhead = head
            while head and head.next:
                t = head.next.next
                if not t:
                    break
                head.next.next = t.next
                head = t
            return newhead.next
if __name__ == "__main__":
    nums = [1,2,3,4,5,6,7,8]
    m, n = 2, 4
    l = LinkList()
    h = l.create_list(nums)
    l.print_list(h)
    app = Solution()
    newh = app.reverse(h)
    l.print_list(newh)
