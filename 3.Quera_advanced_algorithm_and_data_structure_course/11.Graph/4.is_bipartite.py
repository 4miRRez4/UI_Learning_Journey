n, m = map(int, input().split())
adj_list = list()
for i in range(n+10):
    adj_list.append(list())

for i in range(m):
    vi, vj = map(int, input().split())
    adj_list[vi].append(vj)
    adj_list[vj].append(vi)

visited = [False for _ in range(n+1)]
color = [0 for _ in range(n+1)]
bipartite = True

def dfs(v, parent):
    visited[v] = True

    if(parent == -1):
        color[v] = 1
    else:
        color[v] = 1 - color[parent]

    for neighbor in adj_list[v]:
        if not visited[neighbor]:
            dfs(neighbor, v)
        elif color[v] == color[neighbor]:
            global bipartite
            bipartite = False

for v in range(n+1):
    if not visited[v]:
        dfs(v, -1)

if bipartite:
    print("YES")
else:
    print("NO")

