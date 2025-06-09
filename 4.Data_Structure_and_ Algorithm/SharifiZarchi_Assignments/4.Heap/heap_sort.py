from Max_Heap_array_implementation import Max_Heap

def heap_sort(list_of_nums):
    heap = Max_Heap()
    heap.build_heap_with_bd(list_of_nums)
    for i in range(heap.get_size()):
        print(heap.del_max())

a = [1,2,3]
heap_sort(a)