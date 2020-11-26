import sys
sys.path.append("../")
from create import *

class Solution:
        def partition(self, head: ListNode, x: int) -> ListNode:
            if not head:
                return None
            t1 = ListNode(0)
            t2 = t1.next = head
            head = head.next
            while head:
                print(head.val)
                t = head.next
                if head.val <= t2.val:
                    t1.next = head
                    head.next = t2
                    t2 = head
                else:
                    while t2 != head and head.val >= t2.val:
                        t2 = t2.next
                    head.next = t2.next
                    t2.next = head
                    head.next = None
                head = t
            return t1.next

if __name__ == "__main__":
    nums = [1,4,3,2,5,2]
    x = 3

    l = LinkList()
    h = l.create_list(nums)
    l.print_list(h)
    app = Solution()
    app.partition(h, x)
    l.print_list(h)
