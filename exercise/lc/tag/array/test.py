def largestRectangleArea(heights):
    stack = []
    res = 0
    heights.append(0)
    N = len(heights)
    for i in range(N):
        if not stack or heights[i] > heights[stack[-1]]:
            stack.append(i)
        else:
            while stack and heights[i] <= heights[stack[-1]]:
                h = heights[stack[-1]]
                stack.pop()
                if not stack:
                    w = i
                else:
                    w = i - stack[-1] - 1
                res = max(res, h * w)
            stack.append(i)
    return res
def largestRectangleArea2(heights):
    stack = []
    res = 0
    heights.append(0)
    N = len(heights)
    i = 0
    while i < N:
        print("stack:", stack, "i:", i)
        if not stack or heights[i] > heights[stack[-1]]:
            stack.append(i)
            i += 1
        else:
            h = heights[stack[-1]]
            stack.pop()
            if not stack:
                w = i
            else:
                w = i - stack[-1] - 1
            res = max(res, h * w)
            print("out stack:", stack, "i:", i, "h, w:", h, w)
    return res
if __name__ == "__main__":
    a = [2,1,5,6,2,3]
    #print(a, largestRectangleArea(a))
    #print(a, largestRectangleArea2(a))
