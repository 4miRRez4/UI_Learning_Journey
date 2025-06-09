def upper_bound(a, x):    
    if a[-1] <= x:
        return -1;

    start = 0
    end = len(a)-1

    while end > start + 1:
        mid = start + end >> 1

        if a[mid] > x:
            end = mid
        else:
            start = mid

    return (end, a[end])