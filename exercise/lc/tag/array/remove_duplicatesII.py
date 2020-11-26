'''
Remove Duplicates from Sorted Array
Given a sorted array, remove the duplicates in place such that > each element appear only once
and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example, Given input array A = [1,1,2],
Your function should return length = 2, and A is now [1,2].

Remove Duplicates from Sorted Array II
Follow up for "Remove Duplicates": What if duplicates are allowed at most twice?
For example, Given sorted array A = [1,1,1,2,2,3],
Your function should return length = 5, and A is now [1,1,2,2,3].
'''

def remove_dup(a):
    j = 0;
    cnt = 0
    for i in range(1, len(a)):
        if a[i] == a[j]:
            cnt += 1
            if cnt < 2:
                j += 1
                a[j] = a[i]
        else:
            j += 1
            a[j] = a[i]
            cnt = 0
    return j+1
if __name__ == "__main__":
    indata = input()
    a = indata.split()
    a = [int(x) for x in a]
    j = remove_dup(a)
    print(a[:j])
