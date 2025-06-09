n = int(input())
adj_list = [set() for _ in range(n+1)]

for i in range(n-1):
    u, v = map(int, input().split())
    adj_list[u].add(v)
    adj_list[v].add(u)

q = int(input())
has_people = [False for _ in range(n+1)]

for i in range(q):
    p = int(input())
    has_people[p] = True

def bfs_for_closest(s, adj_list, has_people):
    visited = [False for _ in range(n+1)]

    queue = []
    queue.append(s)
    visited[s] = True

    while(queue):
        v = queue.pop(0)

        if(has_people[v]):
            return v
        
        for neighbor in adj_list[v]:
            if not visited[neighbor]:
                queue.append(neighbor)

print(bfs_for_closest(1, adj_list, has_people))