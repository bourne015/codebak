
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
        for c in word:
            if c not in node.next:
                print("can't find", word)
                return False
            node = node.next[c]
        if node.isword:
            print("get", word)
        else:
            print("can't find", word)
        return node.isword

if __name__ == '__main__':
    app = word_dict()
    app.add('bad')
    app.add('dad')
    app.add('mad')
    app.search('dad')
    app.search('dsd')
    app.search('mad')
