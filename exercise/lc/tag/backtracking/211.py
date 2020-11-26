
class TrieNode():
    def __init__(self):
        self.isword = False
        self.next = {}

class word_dict():
    def __init__(self):
        self.root = TrieNode()

    def add(self, word):
        node = self.root
        for c in word:
            node.next[c] = TrieNode()
            node = node.next[c]
        node.isword = True

    def search(self, word):
        node = self.root
        self.res = False
        self.dfs(node, word)
        if self.res:
            print("get", word)
        else:
            print("can't get", word)
        return self.res

    def dfs(self, node, word):
        if not word:
            if node.isword:
                self.res = True
            return
        if word[0] == '.':
            for c in node.next:
                self.dfs(node.next[c], word[1:])
        else:
            if word[0] in node.next:
                node = node.next[word[0]]
            else:
                self.res = False
                return
            self.dfs(node, word[1:])

if __name__ == '__main__':
    app = word_dict()
    app.add('bad')
    app.add('dad')
    app.add('mad')
    app.search('dad')
    app.search('dsd')
    app.search('d.d')
    app.search('mad')
