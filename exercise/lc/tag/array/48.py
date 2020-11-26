class Solution:
    def combination(self, nums):
        lens = len(nums)
        if lens <= 1:
            return nums
        rounds = lens//2
        cnt = lens-1
        for row in range(rounds):
            self.round_sp(nums, lens, row, cnt)
            cnt -= 2

    def round_sp(self, nums, lens, row, cnt):
        for cul in range(row, row+cnt):
            tmp = nums[row][cul]
            nums[row][cul] = nums[lens-1-cul][row]
            nums[lens-1-cul][row] = nums[lens-1-row][lens-1-cul]
            nums[lens-1-row][lens-1-cul] = nums[cul][lens-1-row]
            nums[cul][lens-1-row] = tmp

if __name__ == "__main__":
    #a = [[1,2,3,4], [5,6,7,8], [9,10,11,12], [13,14,15,16]]
    #a = [[1,2,3], [4,5,6], [7,8,9]]
    inp = int(input())
    a, i = [], 1
    for _ in range(inp):
        t = []
        for _ in range(inp):
            t.append(i)
            i += 1
        a.append(t)
    app = Solution()
    for row in a:
        print(row)
    app.combination(a)
    print("spyin")
    for row in a:
        print(row)
