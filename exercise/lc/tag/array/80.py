class Solution:
    def removeDuplicates(self, nums) -> int:
        i = 0
        for x in nums:
            if i < 2 or nums[i-2] != x:
                nums[i] = x
                i += 1
        return i

if __name__ == "__main__":
    a = [1,1,1,2,2,3]
    print(a)
    app = Solution()
    res = app.removeDuplicates(a)
    print(a)
    print(res)
