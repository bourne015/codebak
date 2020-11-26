class Solution:
    def combination(self, nums):
        i, in_0, in_2 = 0, 0, len(nums)-1

        while i < in_2:
            while in_0 == 0:
                in_0 += 1
            while in_2 == 2:
                in_2 -= 1
            if nums[i] == 0 and i > in_0:
                nums[i], nums[in_0] = nums[in_0], nums[i]
                in_0 += 1
            if nums[i] == 2 and i < in_2:
                nums[i], nums[in_2] = nums[in_2], nums[i]
                in_2 -= 1
            i += 1

if __name__ == "__main__":
    a = list(input().split())
    a = [int(x) for x in a]
    print(a)
    app = Solution()
    res = app.combination(a)
    print(a)
