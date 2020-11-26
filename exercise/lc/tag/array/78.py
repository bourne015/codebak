class Solution:
    def subsets(self, nums):
        res = []
        self.dfs(nums, 0, [], res)
        return res

    def dfs(self, nums, index, tmp, res):
        res.append(tmp)
        for i in range(index, len(nums)):
            self.dfs(nums, i+1, tmp+[nums[i]], res)

if __name__ == "__main__":
    a = list(input().split())
    a = [int(x) for x in a]
    print(a)
    app = Solution()
    res = app.subsets(a)
    print(res)
