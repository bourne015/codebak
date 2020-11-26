class Solution:
    def combination(self, nums, lens):
        if lens%2 == 0:
            rounds = lens//2
        else:
            rounds = lens//2 + 1
        cnt, step = lens, 1
        for row in range(rounds):
            step = self.round_sp(nums, lens, row, cnt, step)
            cnt -= 2

    def round_sp(self, nums, lens, row, cnt, step):
        res = []
        #top
        for i in range(cnt):
            nums[row][row+i] = step
            step += 1
        #right
        for i in range(1,cnt):
            nums[row+i][row+cnt-1] = step
            step += 1
        #bottom
        for i in range(1,cnt):
            nums[row+cnt-1][row+cnt-1-i] = step
            step += 1
        #left
        for i in range(1,cnt-1):
            nums[row+cnt-1-i][row] = step
            step += 1
        return step

if __name__ == "__main__":
    #a = [[1,2,3], [4,5,6], [7,8,9]]
    a = int(input())
    nums = [[0 for _ in range(a)] for _ in range(a)]
    app = Solution()
    app.combination(nums, a)
    for i in nums:
        print(i)
