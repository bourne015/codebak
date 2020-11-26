import sys
sys.path.append("../")
from create import *

class Solution:
        def mergeTwoLists(self, l1, l2):
            if not l1:
                return l2
            if not l2:
                return l1
            head = t = ListNode(0)
            while l1 and l2:
                if l1.val < l2.val:
                    t.next = l1
                    l1 = l1.next
                else:
                    t.next = l2
                    l2 = l2.next
                t = t.next
            if l1:
                t.next = l1
            if l2:
                t.next = l2
            return head.next
if __name__ == "__main__":
    nums1, nums2 = [1,3,5,7,9], [2,4,6,8]
    #nums = [1,4,3]

    l = LinkList()
    h1 = l.create_list(nums1)
    h2 = l.create_list(nums2)
    l.print_list(h1)
    l.print_list(h2)
    app = Solution()
    newh = app.mergeTwoLists(h1, h2)
    l.print_list(newh)
