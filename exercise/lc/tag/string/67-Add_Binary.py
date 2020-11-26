
def addbin(a, b):
    na,nb = len(a),len(b)
    if na > nb:
        n = nb
        s = a[0:na-nb]
    else:
        n = na
        s = a[0:nb-na]
    inc = 0
    res = []
    for i in range(1, n+1):
        bit = int(a[-i]) + int(b[-i]) + inc
        if bit > 1:
            inc = 1
        else:
            inc = 0
        bit  = bit%2
        res.insert(0, str(bit))
    for i in s[-1::-1]:
        bit  = int(i) + inc
        if bit > 1:
            inc = 1
        else:
            inc = 0
        bit  = bit%2
        res.insert(0, str(bit))
    if inc:
        res.insert(0, "1")
    return "".join(res)
if __name__ == "__main__":
    indata = input()
    a = indata.split()
    print(indata, addbin(a[0], a[1]))
