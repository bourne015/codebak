def Find(self, target, array):
    pass
if __name__ == "__main__":
    target=input()
    array = []
    for i in range(0, 2):
    	temp = []
        temp=input("array:\n").strip().split(' ')
        array.append(temp)
    print(target,array)
