class Solution:
    def combination(self, nums, target: int):
        res = []
        if not nums:
            return res
        self.dfs(nums, 0, len(nums), target, res, [])
        return res
    def dfs(self, nums, index, n, target, res, tmp):
        if target == 0:
            res.append(tmp)
            return
        for i in range(index, n):
            if target-nums[i] >= 0:
                self.dfs(nums, i, n, target-nums[i], res, tmp+[nums[i]])
            else:
                return
if __name__ == "__main__":
    a, t = [2,3,6,7], 7
    app = Solution()
    res = app.combination(a, t)
    print(a, t)
    print(res)
