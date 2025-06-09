import queue

n = int(input())
idols = list(map(int, input().split()))
S = [i for i in range(1,n+1)]

counter = [0] * n
for i in range(n):
    counter[idols[i]-1] += 1

zeros = queue.Queue(maxsize=n)

for i in range(n):
    if(counter[i] == 0):
        zeros.put(i+1)

while(zeros.empty() == False):
    deleted = zeros.get()
    S.remove(deleted)
    counter[idols[deleted-1]-1] -= 1
    if(counter[idols[deleted-1]-1] == 0):
        zeros.put(idols[deleted-1])

l = len(S)
print(l)
for i in range(l):
    print(S[i], end=" ")