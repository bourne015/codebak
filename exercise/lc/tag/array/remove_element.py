'''
Given an array and a value, remove all instances of that > value in place and return the new length.
The order of elements can be changed. It doesn't matter what you leave beyond the new length
'''

def remove_element(a):
    j = 0
    for i,x in enumerate(a):
        if x == target:
            continue
        a[j] = x
        j = j+1
    return j
if __name__ == "__main__":
    indata = input()
    s = indata.split(";")
    target = int(s[1])
    a = s[0].split()
    a = [int(x) for x in a]
    print(a)
    j = remove_element(a)
    print(a[:j])
