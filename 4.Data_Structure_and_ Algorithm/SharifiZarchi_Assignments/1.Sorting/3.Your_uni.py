import numpy as np

n, k = map(int, input().split())

a = list(map(int, input().split()))
b = list(map(int, input().split()))

count = [0 for _ in range(1000)]

for i in range(n):
    diff = abs(a[i] - b[i])
    count[diff] += 1

last = np.max(np.nonzero(count))
while(last >= 0):
    if(k > count[last]):
        k -= count[last]
        count[last-1] += count[last]
        count[last] = 0
        last -= 1
    else:
        count[last] -= k
        count[last-1] += k
        k = 0
        break

print(count)