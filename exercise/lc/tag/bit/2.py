
def twofunc(a):
    if a < 0:
        return False
    while a > 0:
        if a & 0x1:
            if a > 0x1:
                return False
        a = a>>1
    return True
if __name__ == "__main__":
    a = int(input())
    print(a, twofunc(a))
