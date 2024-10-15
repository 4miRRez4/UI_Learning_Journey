n = int(input())
heights =  list(map(int, input().split()))

max_area = 0
for i in range(n):
    tmpIdx = i+1
    while(tmpIdx < n and heights[tmpIdx] >= heights[i]):
        tmpIdx += 1
    right = tmpIdx-1

    tmpIdx = i-1
    while(tmpIdx > -1  and heights[tmpIdx] >= heights[i]):
        tmpIdx -= 1
    left = tmpIdx+1

    if((right-left)*heights[i] > max_area):
        max_area = (right-left+1)*heights[i]

print(max_area)