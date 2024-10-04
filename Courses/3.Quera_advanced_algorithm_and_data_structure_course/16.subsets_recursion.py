def all_subsets_using_recursion(arr, n, aux, ind):
    if(ind == n):
        for i in range(n):
            if(aux[i] != -1):
                print(aux[i], end=' ')
        print()
        return
    
    aux[ind] = -1
    all_subsets_using_recursion(arr, n, aux, ind+1)

    aux[ind] = arr[ind]
    all_subsets_using_recursion(arr, n, aux, ind+1)



arr = list(map(int, input().split()))
aux = [-1] * len(arr)
all_subsets_using_recursion(arr, len(arr), aux, 0)