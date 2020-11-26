import heapq
def frequencySort(s):
    dic, heap, res = {}, [], ""
    for i in s:
        if i not in dic:
            dic[i] = 1
        else:
            dic[i] += 1
    for a in dic:
        heapq.heappush(heap, (-1*dic[a], a))
    while heap:
        val = heapq.heappop(heap)
        res += val[1]*(-1*val[0])
    return res

if __name__ == "__main__":
    #a = "1223334444"
    a = str(input())
    res = frequencySort(a)
    print(a, res)
