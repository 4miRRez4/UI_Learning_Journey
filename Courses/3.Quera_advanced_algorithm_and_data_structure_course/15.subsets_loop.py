def all_subsets_using_loop(input_list):
    subsets = [[]]  
    for element in input_list:
        current_subsets = subsets.copy() 
        for subset in current_subsets:
            new_subset = subset + [element]
            subsets.append(new_subset)

    for subset in subsets:
        print(subset)


arr = list(map(int, input().split()))
all_subsets_using_loop(arr)