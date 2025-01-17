import sys
sys.setrecursionlimit(10**5 + 100)

def has_path(s, t, adj_list, visited):
    if(s == t):
        return True
    
    visited[s] = True

    for neighbor in adj_list[s]:
        if(visited[neighbor] == False):
            if(has_path(neighbor, t, adj_list, visited)):
                return True
    
    return False


n, m = map(int, input().split())
s, t = map(int, input().split())

adj_list = [[] for j in range(n+1)]
visited = [False for i in range(n+1)]

for i in range(m):
    vi, vj = map(int, input().split())
    adj_list[vi].append(vj)
    adj_list[vj].append(vi)

if(has_path(s, t, adj_list, visited)):
    print("YES")
else:
    print("NO")