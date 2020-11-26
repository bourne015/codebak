import sys
sys.path.append("../")
from create import *

class Solution:
        def deleteDuplicates(self, head):
            if not head or not head.next:
                return head
            dum = t = ListNode(0)
            while head:
                cnt = 1
                nex = head.next
                while head and nex and head.val == nex.val:
                    cnt += 1
                    nex = nex.next
                if cnt == 1:
                    t.next = head
                    t = t.next
                    t.next = None
                if nex:
                    head = nex
                else:
                    head = None
            return dum.next
if __name__ == "__main__":
    nums = [1,2,3,3,3,4,4]

    l = LinkList()
    h = l.create_list(nums)
    l.print_list(h)
    app = Solution()
    newh = app.deleteDuplicates(h)
    l.print_list(newh)
