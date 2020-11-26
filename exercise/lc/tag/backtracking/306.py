#unfinished

class Solution:
    def additive(self, num):
        res = []
        self.dfs(res, nums, [], 0)
        return res

    def dfs(self, res, nums, tmp, index):
        if len(tmp) == 3 and target > 0:
            res.append(tmp)
            return
        for i in range(index, len(nums)):
            self.dfs(res, nums,tmp+[nums[i]], i+1)

if __name__ == "__main__":
    s = '199100199'
    app = Solution()
    res = app.additivenumber(s)
    print(s, res)
