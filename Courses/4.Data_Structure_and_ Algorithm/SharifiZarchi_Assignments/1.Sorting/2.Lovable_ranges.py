n = int(input())
x_and_ys = []
for i in range(n):
    given = input().split()
    x_and_ys += [int(given[0])]
    x_and_ys += [int(given[1])]
    print(x_and_ys)