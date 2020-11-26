
def decodeString(s):
    return dfs(s, 0)

def dfs(s, i):
    tmp = ""
    n = len(s)
    while i < n and s[i] != ']':
        if s[i].isalpha():
            tmp += s[i]
            i += 1
        else:
            cnt = 0
            while s[i].isdigit():
                cnt = cnt*10 + int(s[i])
                i += 1
            i += 1
            t = dfs(s, i)
            i += 1
            while cnt > 0:
                tmp += t
                cnt -= 1
    return tmp

if __name__ == "__main__":
    a = "2[ab]3[cd]f"
    print(a)
    res = decodeString(a)
    print(res)
