class Solution:
    def rotate(self, nums, k):
        n = len(nums)
        k = k%n
        for _ in range(k):
            t = nums[-1]
            for i in range(n-1, 0, -1):
                nums[i] = nums[i-1]
            nums[0] = t

    def rotate2(self, nums, k):
        n = len(nums)
        k = k%n
        for i in range((n-k)/2):
            t = nums[i]
            nums[i] = nums[n-k-1-i]
            nums[n-k-1-i] = t
        for i in range(n-k, k/2):
            t = nums[i]
            nums[i] = nums[]
if __name__ == "__main__":
    a, k = [1,2,3,4,5,6,7], 3
    print(a, k)
    app = Solution()
    app.rotate(a, k)
    print(a)
