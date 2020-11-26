
import sys
sys.path.append("../")
from create import *

class Solution:
    def mergeKLists(self, data):
        if not data:
            return None
        if len(data) == 1:
            return data[0]
        mid = len(data)//2
        left = self.mergeKLists(data[:mid])
        right = self.mergeKLists(data[mid:])
        return self.merge(left, right)

    def merge(self, left, right):
        fake = t = ListNode(0)
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

if __name__ == "__main__":
    a = [[1,4,5],[1,3,4], [2,6]]
    l = LinkList()
    data = []
    for i in a:
        h = l.create_list(i)
        l.print_list(h)
        data.append(h)

    app = Solution()
    head = app.mergeKLists(data)
    l.print_list(head)
