class Solution:
    def combination(self, nums):
        flag = []
        for i, row in enumerate(nums):
            for j, a in enumerate(row):
                if a == 0:
                    flag.append((i, j))

        for (row, cul) in flag:
            for j in range(len(nums[0])):
                nums[row][j] = 0
            for i in range(len(nums)):
                nums[i][cul] = 0

if __name__ == "__main__":
    a = [[0,2,3,4], [5,0,7,8], [9,10,11,12], [13,14,15,16]]
    #a = [[1,2,3], [4,5,6], [7,8,9]]
    app = Solution()
    for row in a:
        print(row)
    app.combination(a)
    print("res:")
    for row in a:
        print(row)
