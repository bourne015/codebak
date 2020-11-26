class Solution:
    def generatePalindromes(self, s):
        res = []
        if len(s) <= 1:
            return res
        n = len(s)
        self.dfs(res, s, n,"")
        return res

    def dfs(self, res, s, n, tmp):
        if n == 0 and self.is_Palindromes(tmp):
            if tmp not in res:
                res.append(tmp)
        for i in range(0, len(s)):
            self.dfs(res, s[:i]+s[i+1:], n-1, tmp+s[i])

    def is_Palindromes(self, s):
        return s == s[::-1]
if __name__ == "__main__":
    s = input()
    app = Solution()
    res = app.generatePalindromes(s)
    print(res)
