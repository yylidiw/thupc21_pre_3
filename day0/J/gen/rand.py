import random

def gen(n, k, filename):
    with open(filename, "w", encoding="ascii") as f:
        f.write(f"{n} {k}\n")

random.seed(2077)
m, i = map(int, input().split(' '))
for t in range(m):
    k = random.randint(1, 4)
    n = random.randint(2 ** k, 500)
    print(n, k)
    gen(n, k, f"{i}.in")
    i += 1