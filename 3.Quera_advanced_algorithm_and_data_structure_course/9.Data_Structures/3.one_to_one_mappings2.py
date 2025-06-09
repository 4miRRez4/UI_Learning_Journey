n = int(input())
idols = list(map(int, input().split()))

deg = [0] * n
zeros_q = [0] * n
deleted_flag = [False] * n

start = 0
size_q = 0

for i in range(n):
    idols[i] = idols[i] - 1
    deg[idols[i]] += 1

for i in range(n):
    if(deg[i] == 0):
        zeros_q[start+size_q] = i
        size_q += 1
    
not_del_cnt = n
while(size_q != 0):
    deleted_flag[zeros_q[start]] = True

    deg[idols[zeros_q[start]]] -= 1
    if(deg[idols[zeros_q[start]]] == 0):
        zeros_q[start+size_q] = idols[zeros_q[start]]
        size_q += 1

    not_del_cnt -= 1
    start += 1
    size_q -= 1

print(not_del_cnt)
for i in range(n):
    if(deleted_flag[i] == False):
        print(i+1, end=" ")