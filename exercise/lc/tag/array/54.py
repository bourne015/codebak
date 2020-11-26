class Solution:
    def combination(self, nums):
        lens = len(nums)
        if lens%2 == 0:
            rounds = lens//2
        else:
            rounds = lens//2 + 1
        cnt = lens
        for row in range(rounds):
            self.round_sp(nums, lens, row, cnt)
            cnt -= 2

    def round_sp(self, nums, lens, row, cnt):
        res = []
        #top
        for i in range(cnt):
            res.append(nums[row][row+i])
        #right
        for i in range(1,cnt):
            res.append(nums[row+i][row+cnt-1])
        #bottom
        for i in range(1,cnt):
            res.append(nums[row+cnt-1][row+cnt-1-i])
        #left
        for i in range(1,cnt-1):
            res.append(nums[row+cnt-1-i][row])
        print(res)

if __name__ == "__main__":
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
