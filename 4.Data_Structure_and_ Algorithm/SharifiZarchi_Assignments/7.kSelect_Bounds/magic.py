def magic_function(a, x):    
    if a[0] <= x:
        return -1

    start = 0
    end = len(a)-1

    while end > start + 1:
        mid = (start + end) >> 1

        if a[mid] > x:
            start = mid
        else:
            end = mid

    return (start, a[start])