
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

    def merge(self, left, right):
        fake = ListNode(0)
        t = fake
        while left and right:
            if left.val < right.val:
                t.next = left
                left = left.next
            else:
                t.next = right
                right = right.next
            t = t.next
        if left:
            t.next = left
        elif right:
            t.next = right
        return fake.next

    def SortList(self, head):
        if not head or not head.next:
            return head

        fast, slow = head.next, head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
        right = self.SortList(slow.next)
        slow.next = None
        left = self.SortList(head)
        return self.merge(left, right)
if __name__ == "__main__":
    a = [4,2,1,3]
    l = LinkList()
    head = l.create_list(a)
    l.print_list(head)

    app = Solution()
    head = app.SortList(head)
    l.print_list(head)
