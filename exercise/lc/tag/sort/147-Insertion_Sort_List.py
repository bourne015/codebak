
import sys
sys.path.append("../")
from create import *

class Solution:
    def insertionSortList(self, head: ListNode) -> ListNode:
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
    a = [4,2,1,3]
    l = LinkList()
    head = l.create_list(a)
    l.print_list(head)

    app = Solution()
    head = app.insertionSortList(head)
    l.print_list(head)
