n = int(input())
nums = list(map(int, input().split()))

expected_sum = 0
for i in range(n-1):
    expected_sum += nums[i]
print(n*(n+1)//2 - expected_sum)

# is_there_list = [False] * (n)
# for i in range(n-1):
#     is_there_list[nums[i]-1] = True
# for i in range(n):
#     if(is_there_list[i] == False):
#         print(i+1)
#         break