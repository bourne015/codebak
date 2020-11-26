

def string_merge(s):
    dic, res = {}, []
    for x in s:
        t = ''
        for i in x:
            c = str((ord(i)-ord(x[0])+26)%26)
            t = t+c
        if t in dic:
            dic[t].append(x)
        else:
            dic[t] = [x]
    for x in dic:
        res.append(dic[x])
    return res

if __name__ == "__main__":
    s = ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"]
    res = string_merge(s)
    print(s)
    print(res)
