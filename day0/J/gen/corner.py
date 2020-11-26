def gen(n, k, filename):
    with open(filename, "w", encoding="ascii") as f:
        f.write(f"{n} {k}\n")

i = int(input())
for k in range(1, 5):
    for n in range(2 ** k, (2 ** k) + k + 1):
        gen(n, k, f"{i}.in")
        i += 1
    gen(500, k, f"{i}.in")
    i += 1
