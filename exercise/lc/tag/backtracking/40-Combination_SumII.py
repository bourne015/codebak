class Solution:
        def combinationSum(self, candidates, target: int):
            res = []
            candidates.sort()
            self.dfs(candidates, target, res, [], 0)
            return res
        def dfs(self, candidates, t, res, path, index):
            if t < 0:
                return
            elif 0 == t:
                if path not in res:
                    res.append(path)
            else:
                for i in range(index, len(candidates)):
                    self.dfs(candidates, t-candidates[i], res, path+[candidates[i]], i+1)


if __name__ == "__main__":
    can = [10,1,2,7,6,1,5]
    t = 8
    app = Solution()
    res = app.combinationSum(can, t)
    print(res)
