def bubble_sort(nums, types, n):
    for i in range(n-1):
        all_sorted = True  
        for j in range(n-1-i):
            if(nums[j] > nums[j+1]):
                nums[j], nums[j+1] = nums[j+1], nums[j]
                if(types[j] != types[j+1]):
                    types[j], types[j+1] = types[j+1], types[j]
                all_sorted = False
        if(all_sorted):
            break


n = int(input())
x_and_ys = []
types = [] # 1=>start, 0=>end;
for i in range(n):
    x, y = map(int, input().split())
    x_and_ys.extend([x, y])
    types += [1]
    types += [0]

bubble_sort(x_and_ys, types, n*2)


cnt = [0] * n
size_of_range = 0
for i in range(2*n -1):
    if(types[i] == 1):
        size_of_range+=1
    else:
        cnt[size_of_range-1] += 1
        size_of_range-=1

    cnt[size_of_range-1] += x_and_ys[i+1] - x_and_ys[i]

#cnt[0] += 1 # last end
for i in range(n):
    print(cnt[i])