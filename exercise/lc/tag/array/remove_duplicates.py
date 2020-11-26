'''
Remove Duplicates from Sorted Array
Given a sorted array, remove the duplicates in place such that > each element appear only once
and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example, Given input array A = [1,1,2],
Your function should return length = 2, and A is now [1,2].
'''

def remove_dup(a):
    j = 0;
    for i in range(1, len(a)):
        if a[i] == a[j]:
            continue
        j += 1
        a[j] = a[i]
    return j
if __name__ == "__main__":
    indata = input()
    a = indata.split()
    a = [int(x) for x in a]
    j = remove_dup(a)
    print(a[:j])
