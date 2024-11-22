n = int(input())
arr = [*map(int, input().split())]
arr = [0] + arr + [0]
stack = []
ranges = []

for i in range(n+1):
    a = arr[i]
    b = arr[i+1]

    while(a < b):
        a += 1
        stack.push(i+1)

    while(a > b):
        a -= 1
        ranges.append((stack.pop(), i))

print(len(ranges))
for pair in ranges:
    print(pair[0], pair[1])