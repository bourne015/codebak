
class Solution:
    def minimumtital(self, nums):
        res,tmax,tmin,rmax,rmin = 0,1,1,1,1
        for x in nums:
            tmax, tmin = tmax * x, tmin * x
            rmax, rmin = max(max(tmax, tmin), x), min(min(tmax, tmin), x)
            res = max(res, rmax)
        return res

if __name__ == "__main__":
    tri = [2,3,-2,4]
    app = Solution()
    ret = app.minimumtital(tri)
    print(tri)
    print(ret)

