n = int(input())
locs = []
adj_list = [[] for _ in range(n+1)]

for v in range(n):
    x, y = map(int, input().split())
    locs.append((x, y))

    for l in range(v):
        if(locs[l].first == x or locs[l].second == y):
            adj_list[l].append[v]
            adj_list[v].append[l]


def dfs(s, adj_list, visited):
    stack = []
    stack.append(s)

    while(stack.empty() == False):
        v = stack[-1]
        stack.pop(-1)

        visited[v] = True

        for neighbor in adj_list[v]:
            if(visited[neighbor] == False):
                stack.append(neighbor)


def num_of_components(n):
    components = 0
    visited = [False for _ in range(n+1)]

    for i in range(1, n+1):
        if(visited[i] == False):
            components += 1
            dfs(i, adj_list, visited)
        
    return components




print(num_of_components(n) - 1)

    