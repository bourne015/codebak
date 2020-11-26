class Solution:
    def threesumsmall(self, nums, target):
        res = []
        self.dfs(res, nums, target, [], 0)
        return res

    def dfs(self, res, nums, target, tmp, index):
        if len(tmp) == 3 and target > 0:
            res.append(tmp)
            return
        for i in range(index, len(nums)):
            if nums[i] > target:
                break
            self.dfs(res, nums, target-nums[i], tmp+[nums[i]], i+1)

if __name__ == "__main__":
    a = [-2,0,1,3]
    t = 2
    app = Solution()
    res = app.threesumsmall(a, t)
    print(res)
