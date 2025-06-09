import queue

def bfs(s, t, adj_list, dist, prev):
    q = queue.Queue()
    q.put(s)

    while(q.empty() == False):
        node = q.get()

        for neighbor in adj_list[node]:
            if(dist[neighbor] > dist[node] + 1):
                dist[neighbor] = dist[node] + 1
                prev[neighbor] = node
                q.put(neighbor)


def shortest_path(s, t, adj_list):
    dist = [float('inf') for i in range(n+1)]
    dist[s] = 0

    prev = [-1 for i in range(n+1)]

    bfs(s, t, adj_list, dist, prev)

    if(dist[t] == float('inf')):
        return []
    
    path = []
    current = t
    while(current != -1):
        path.append(current)
        current = prev[current]

    path.reverse()
    return path
            


n, m = map(int, input().split())
s, t = map(int, input().split())

adj_list = [[] for i in range(n+1)]
for i in range(m):
    vi, vj = map(int, input().split())
    adj_list[vi].append(vj)
    adj_list[vj].append(vi)


p = shortest_path(s, t, adj_list)
if(len(p) == 0):
    print(-1)
else:
    print(len(p))
    print(p)