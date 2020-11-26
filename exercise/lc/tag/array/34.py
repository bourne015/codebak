class Solution:
    def searchRange(self, nums, target: int):
        res = [-1, -1]
        if not nums:
            return res
        l, r = 0, len(nums)-1
        while l <= r:
            mid = (l+r)//2
            if nums[mid] < target:
                l = mid+1
            else:
                r = mid-1
        res[0] = l

        l, r = 0, len(nums)-1
        while l <= r:
            mid  = (l+r)//2
            if nums[mid] > target:
                r = mid-1
            else:
                l = mid+1
        res[1] = r
        if res[0] < res[1]:
            return res
        else:
            return [-1, -1]

if __name__ == "__main__":
    a = [1,2,3,3,4,5,6]
    t = 3
    app = Solution()
    res = app.searchRange(a, t)
    print(a, t)
    print(res)
