n = int(input())
dest = list(map(int, input().split()))

ascending = []
for i in range(1, n+1):
    ascending.append(i)

def fact_base(perm):
    res = 0
    b = 1
    for i in range(len(perm)):
        b *= (i+1)
        res += b*perm[i]
    
    return res


#BFS. nodes are corresponding fact base. connecting edges along the way.
def bfs_path_len(start_perm, dest_perm, max_fact_base):
    visited = [False for _ in range(max_fact_base+10)]

    queue = []
    queue.append((start_perm, 0)) #second = path_len
    visited[fact_base(start_perm)] = True
        

    while(queue):
        curr = queue.pop(0)
        curr_perm = curr[0]
        path_len_till_curr = curr[1]

        if(dest_perm == curr_perm):
            return path_len_till_curr

        #generate adjacency nodes
        for x in range(1, n):
            new_perm = curr_perm[0:x+1][::-1] + curr_perm[x+1:]
            new_perm_based = fact_base(new_perm)

            if not visited[new_perm_based]:
                visited[new_perm_based] = True
                queue.append((new_perm, path_len_till_curr + 1))



max_fact_base = fact_base(ascending)
print(bfs_path_len(ascending, dest, max_fact_base))