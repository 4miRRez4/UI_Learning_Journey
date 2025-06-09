n = int(input())
adj_list = [[] for _ in range(n)]

for i in range(n):
    for j in range(n):
        if(i != j):
            adj_list[i].append(j)

permutations = []

def dfs(start, adj_list, visited, path):
    if(len(path) == n):
        permutations.append(path)
        print(path)
        return
    
    visited[start] = True
    for neighbor in adj_list[start]:
        if not visited[neighbor]:
            dfs(neighbor, adj_list, visited, path + str(neighbor))
    visited[start] = False




for start in range(n):
    visited = [False for _ in range(n)]
    dfs(start, adj_list, visited, str(start))

print(permutations)