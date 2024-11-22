n = int(input())
heights = list(map(int, input().split()))

stack_heights = []
for i in range(n):
    if(len(stack_heights) != 0 and heights[i] % 2 == stack_heights[-1]):
        stack_heights.pop()
    else:
        stack_heights.append(heights[i] % 2)

if(len(stack_heights) <= 1):
    print("YES")
else:
    print("NO")

