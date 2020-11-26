import sys
sys.path.append("../")
from create import *

class Solution:
        def findStrobogrammatic(self, n):
            res = []
            dic = {"0":"0","1":"1", "6":"9", "8":"8", "9":"6"}
            #generate the left half
            self.dfs(res, "", dic, 0, n//2)

            #append the right half
            cnt = len(res)
            for i in range(cnt):
                for j in range(n//2-1, -1, -1):
                    res[i] += dic[res[i][j]]

            #if n is odd, insert the mid letter
            if n%2 != 0:
                for i in range(cnt):
                    tmp = res[0]
                    for c in "018":
                        res.append(tmp[0:n//2]+c+tmp[n//2:])
                    res.pop(0)
            return res

        def dfs(self, res, tmp, dic, i, n):
            if n == i:
                res.append(tmp)
                return
            for c in dic:
                if i == 0 and c == "0":
                    continue
                self.dfs(res, tmp+c, dic, i+1, n)

        def findStrobogrammatic2(self, n):
            res = []
            self.find(res, n, n)
            return res

        def find (self, res, m, n):
            if m == 0:
                res += [""]
                return
            if m == 1:
                res += ["0", "1", "8"]
                return
            self.find(res, m-2, n)
            cnt = len(res)
            for i in range(cnt):
                s = res.pop(0)
                if m != n:
                    res.append("0"+s+"0")
                res.append("1"+s+"1")
                res.append("6"+s+"9")
                res.append("8"+s+"8")
                res.append("9"+s+"6")


if __name__ == "__main__":
    n  = int(input())
    app = Solution()
    res = app.findStrobogrammatic2(n)
    print(res)
