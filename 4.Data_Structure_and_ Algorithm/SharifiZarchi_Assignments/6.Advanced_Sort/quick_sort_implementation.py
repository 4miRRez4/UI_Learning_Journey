def partition(arr, left, right):
    pivot = arr[right]
    leftPtr = left
    rightPtr = right-1

    while True:
        while (leftPtr <= rightPtr and arr[leftPtr] <= pivot):
            leftPtr += 1
            
        while (rightPtr >= leftPtr and arr[rightPtr] > pivot):
            rightPtr -= 1

        if(leftPtr < rightPtr):
            arr[leftPtr], arr[rightPtr] = arr[rightPtr], arr[leftPtr]
        else:
            break

    arr[leftPtr], arr[right] = arr[right], arr[leftPtr]
    return leftPtr

def quick_sort(arr, left, right):
    if(right <= left):
        return
    
    div = partition(arr, left, right)

    quick_sort(arr, left, div-1)
    quick_sort(arr, div+1, right)

arr = [19,97,22,50,93,31,72,11,46]
quick_sort(arr, 0, len(arr)-1)
print(arr)
    