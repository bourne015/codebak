

def reversestr(s):
    '''i, l = 0, len(s)-1
    while i < l:
        s[i], s[l] = s[l], s[i]
        i += 1
        l -= 1
        '''
    s = s[::-1]
    print(s)
    return s
if __name__ == "__main__":
    s = list(input())
    s=reversestr(s)
    print(s)
