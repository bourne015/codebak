import sys
sys.path.append("../")
from create import *

class Solution:
        def sort0(self, head):
            if not head or not head.next:
                return head
            t1 = ListNode(0)
            t1.next = head
            head = head.next
            t1.next.next = None
            while head:
                t = head.next
                t2 = t1
                while t2.next and head.val > t2.next.val:
                    t2 = t2.next
                head.next = t2.next
                t2.next = head
                head = t
            return t1.next

if __name__ == "__main__":
    nums = [4,1,3,2,5,2]
    #nums = [1,4,3]

    l = LinkList()
    h = l.create_list(nums)
    l.print_list(h)
    app = Solution()
    newh = app.sort0(h)
    l.print_list(newh)
