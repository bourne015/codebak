import collections

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class Tree:
    def create_levelold(self, data):
        root = TreeNode(data[0])
        queue = [root]
        i = 1
        while i < len(data):
            node = queue.pop(0)
            if node:
                if i < len(data):
                    node.left = TreeNode(data[i])
                    queue.append(node.left)
                    i += 1
                if i < len(data):
                    node.right = TreeNode(data[i])
                    queue.append(node.right)
                    i += 1
        return root
    def create_level(self, data):
        if not data:
            return None
        root = TreeNode(data[0])
        queue = [root]
        i, n = 1, len(data)
        while queue and i+1 < n:
            node = queue.pop(0)
            if i+1 < n and data[i] != None:
                node.left = TreeNode(data[i])
                queue.append(node.left)
            else:
                #if node:
                #    node.left = None
                queue.append(None)
            if i+1 < n and data[i+1] != None:
                node.right = TreeNode(data[i+1])
                queue.append(node.right)
            else:
                #node.right = None
                queue.append(None)
            i += 2
        return root
    def print_level(self, root):
        queue = [root]
        while queue:
            node = queue.pop(0)
            #if node and node.val != None:
            if node:
                print(node.val)
                #if node.left:
                queue.append(node.left)
                #if node.right:
                queue.append(node.right)
            else:
                #queue.append(None)
                print("N")
    def print_tree(self, root):
        queue = [(root,0)]
        res = []
        while queue:
            node, level = queue.pop(0)
            if len(res) < level+1:
                res.append([])
            if node:
                res[level].append(node.val)
                queue.append((node.left, level+1))
                queue.append((node.right, level+1))
            else:
                res[level].append('N')
        for l in res[:-1]:
            print(l)

class LinkList:
    def create_list(self, data):
        if not data:
            return None
        head = ListNode(data[0])
        p = head
        for x in data[1:]:
            p.next = ListNode(x)
            p = p.next
        return head

    def print_list(self, head):
        t = head
        while t:
            print(t.val, end = '')
            t = t.next
            if t:
                print(end = '->')
        print()

if __name__ == "__main__":
    #a = [1,3,5,None,None,4,6]
    a = [1,None,5,None,None,4,6]
    tree = Tree();
    t1 = tree.create_level(a)
    tree.print_level(t1)
    #tree.print_tree(t1)

    #print("list:")
    #l = LinkList()
    #h = l.create_list(a)
    #l.print_list(h)
