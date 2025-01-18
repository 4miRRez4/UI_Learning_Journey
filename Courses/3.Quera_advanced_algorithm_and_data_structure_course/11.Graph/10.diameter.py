n = int(input())
adj_list = [[] for _ in range(n+1)]

for i in range(n-1):
    u, v = map(int, input().split())
    adj_list[u].append(v)
    adj_list[v].append(u)

def find_max_dis_dfs(v, dis,  adj_list, visited):
    visited[v] = True
    
    global max_dis_node, max_dis
    if(dis > max_dis):
        max_dis = dis
        max_dis_node = v

    for neighbor in adj_list[v]:
        if not visited[neighbor]:
            find_max_dis_dfs(neighbor, dis+1, adj_list, visited)



visited = [False for _ in range(n+1)]

max_dis_node = 1
max_dis = 0

find_max_dis_dfs(1, 0, adj_list, visited)

visited = [False for _ in range(n+1)]

find_max_dis_dfs(max_dis_node, 0, adj_list, visited)

print(max_dis)