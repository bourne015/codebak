
def findsub(nums):
    res, n = [], len(nums)
    dfs(nums, res, n, 0, [])
    return res

def dfs(nums, res, n, index, tmp):
    if tmp and tmp not in res:
        res.append(tmp)
    for i in range(index, n):
        if tmp and tmp[-1] > nums[i]:
            continue
        dfs(nums, res, n, i+1, tmp+[nums[i]])

if __name__ == "__main__":
    a = [4,6,7,7]
    print(a)
    res = findsub(a)
    print(res)
