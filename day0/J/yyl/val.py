import sys

max_n = 500

def check(num):
    datas = open("../data/{}.in".format(num), "r")

    n, k = datas.readline().split(" ")
    n, k = int(n), int(k)

    if not (1 <= k <= 4):
        return False
    k = 1 << k
    #print("{} {}".format(n,k))
    if k > n:
        return False
    if n > max_n:
        return False

    while True:
        data = datas.readline()
        if not data:
            break
        else:
            return False

    return True 


if __name__ == "__main__":
    for i in range(1,39):
        if not check(i):
            print("Error {}".format(i))
        else:
            print("Pass check {}".format(i))