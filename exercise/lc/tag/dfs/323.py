
def countComponents(n, e):
    adj = [[] for _ in range(n)]
    v = [False for _ in range(n)]
    res = 0
    for a in e:
        adj[a[0]].append(a[1])
        adj[a[1]].append(a[0])
    for i in range(n):
        if not v[i]:
            res += 1
            dfs(adj, v, i)
    return res

def dfs(adj, v, i):
    if v[i]:
        return
    v[i] = True
    for j in range(len(adj[i])):
        dfs(adj, v, adj[i][j])
if __name__ == "__main__":
    e =  [[0, 1], [1, 2], [2, 3], [3, 4]]
    print(e)
    res = countComponents(5, e)
    print(res)
