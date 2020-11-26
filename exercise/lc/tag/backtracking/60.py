class Solution:
        def permu(self, n, k):
            res = []
            nums = [x for x in range(1, n+1)]
            print(nums)
            self.dfs(nums, res, [], k)
            return res
        def dfs(self, nums, res, path, k):
            if not nums:
                print(path, k)
                if k == 0:
                    res.append(path)
                return
            for i in range(len(nums)):
                if i > 0 and nums[i] == nums[i-1]:
                    continue
                if k == 0:
                    break
                self.dfs(nums[:i]+nums[i+1:], res, path+[nums[i]], k-1)


if __name__ == "__main__":
    n, k = [int(x) for x in input().strip().split()]
    app = Solution()
    res = app.permu(n, k)
    print(res)
