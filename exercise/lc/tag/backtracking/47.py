class Solution:
        def permu(self, nums):
            res = []
            self.dfs(nums, res, [])
            return res
        def dfs(self, nums, res, path):
            if not nums:
                res.append(path)
                return
            for i in range(len(nums)):
                if i > 0 and nums[i] == nums[i-1]:
                    continue
                self.dfs(nums[:i]+nums[i+1:], res, path+[nums[i]])


if __name__ == "__main__":
    a = [1,2,2]
    app = Solution()
    res = app.permu(a)
    print(a, '\n',res)
