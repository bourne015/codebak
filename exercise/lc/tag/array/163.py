
class Solution:
    def minimumtital(self, nums, low, high):
        res = []
        for x in nums:
            if x == low+1:
                res.append(str(low))
            elif x > low+1:
                res.append(str(low)+'->'+str(x-1))
            if x == high:
                return res
            low = x + 1

        if low+1 == high:
                res.append(high)
        elif low+1 < high:
                res.append(str(low)+'->'+str(high))
        return res

if __name__ == "__main__":
    a, l, h = [0,1,3,50,75],0,99
    app = Solution()
    ret = app.minimumtital(a, l, h)
    print(a, l, h)
    print(ret)

