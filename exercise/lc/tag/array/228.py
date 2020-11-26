class Solution:
    def summaryRanges(self, nums):
        i, n, res = 0, len(nums), []
        while i < n:
            tmp = str(nums[i])
            j = i+1
            while j <  n and nums[j-1]+1 == nums[j]:
                j += 1
            if j > i+1:
                tmp += "->"+str(nums[j-1])
            res.append(tmp)
            i = j
        return res

if __name__ == "__main__":
    a = [0,2,3,4,6,8,9]
    app = Solution()
    res = app.summaryRanges(a)
    print(a)
    print(res)
