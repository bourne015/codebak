class Solution:
    def wordsearch(self, board, s):
        res = []
        for i in range(len(board)):
            for j in range(len(board[0])):
                if self.dfs(board, s, i, j):
                    return True
        return False

    def dfs(self, board, s, i, j):
        if len(s) == 0:
            return True
        if i<0 or i>=len(board) or j<0 or j>=len(board[0]) or s[0]!=board[i][j]:
            return False
        tmp = board[i][j]
        board[i][j] = '*'
        up = self.dfs(board, s[1:], i-1, j)
        down = self.dfs(board, s[1:], i+1, j)
        right = self.dfs(board, s[1:], i, j+1)
        left = self.dfs(board, s[1:], i, j-1)
        board[i][j] = tmp
        return up or down or right or left

if __name__ == "__main__":
    board = [['a', 'b', 'c', 'e'],
            ['s', 'f', 'c', 's'],
            ['a', 'd', 'e', 'e']]
    a = input()
    print(board)
    print(a)
    app = Solution()
    res = app.wordsearch(board, a)
    print(res)
