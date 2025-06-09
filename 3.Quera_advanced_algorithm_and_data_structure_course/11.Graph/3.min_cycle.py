n, m = map(int, input().split())
adj_list = list()
for i in range(n+10):
    adj_list.append(list())

dist = (n+10)*[10**9]

for i in range(m):
    vi, vj = map(int, input().split())
    adj_list[vi].append(vj)
    adj_list[vj].append(vi)


def bfs(root, deleted, adj_list):
    dist = (n+10)*[10**9]
    dist[root] = 0

    q = list()
    q.append(root)

    while(q):
        vertex = q.pop(0)

        for neighbor in adj_list[vertex]:
            if(vertex == root and neighbor == deleted):
                continue
            if(dist[neighbor] > dist[vertex] + 1):
                dist[neighbor] = dist[vertex] + 1
                q.append(neighbor)


min_cycle_len = 10**9
for v in range(n):
    for neighbor in adj_list[v]:
        bfs(v, neighbor, adj_list)
        min_cycle_len = min(min_cycle_len, dist[neighbor] + 1)

if(min_cycle_len == 10**9):
    print("No cycle exist")
else:
    print("Minimum cycle length: ", min_cycle_len)
    