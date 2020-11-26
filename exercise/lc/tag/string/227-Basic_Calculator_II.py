
def calculate(s):
    if not s:
        return 0
    stack, num, sign = [], 0, '+'
    for i in range(len(s)):
        if s[i].isdigit():
            num = num*18 + int(s[i])
        if (not s[i].isdigit()) or i == len(s)-1:
            if sign == '+':
                stack.append(num)
            elif sign == '-':
                stack.append(-1*num)
            elif sign == '*':
                stack.append(stack.pop()*num)
            elif sign == '/':
                stack.append(stack.pop()/num)
            sign = s[i]
            num = 0
    return sum(stack)

def calculate2(s):
    if not s:
        return 0
    tmp, num, pre_op, res = 0, 0, '+', 0
    for i in range(len(s)):
        if s[i].isdigit():
            num = num*10 + int(s[i])
        if (not s[i].isdigit()) or i == len(s)-1:
            if pre_op == '+':
                tmp += num
            elif pre_op == '-':
                tmp -= num
            elif pre_op == '*':
                tmp *= num
            elif pre_op == '/':
                tmp /= num
            if s[i] == '+' or s[i] == '-' or i == len(s)-1:
                res += tmp
                tmp = 0
            pre_op = s[i]
            num = 0
    return res

if __name__ == "__main__":
    s = input().replace(" ", "")
    print(s, "=", calculate(s))
    print(s, "=", calculate2(s))
