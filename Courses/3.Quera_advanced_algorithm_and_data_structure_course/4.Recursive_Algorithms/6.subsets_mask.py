def all_subsets_using_mask(arr, n):
    for mask in range(1<<n):
        for i in range(n):
            if(mask & 1<<i):
                print(arr[i], end=' ')

arr = list(map(int, input().split()))
all_subsets_using_mask(arr, len(arr))