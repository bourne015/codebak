

class Solution(object):
    def maxProduct(self, nums):
        dp_max, dp_min = [nums[0]]*len(nums), [nums[0]]*len(nums)
        for i in range(1,len(nums)):
            t1 = dp_max[i-1]*nums[i]
            t2 = dp_min[i-1]*nums[i]
            dp_max[i] = max(t1, t2, nums[i])
            dp_min[i] = min(t1, t2, nums[i])
        return max(dp_max)


if __name__ == "__main__":
    a = [-2,3,-4, -5]
    app = Solution()
    ret = app.maxProduct(a)
    print(a)
    print(ret)
