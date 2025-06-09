n, W = map(int, input().split())
arr = []
for _ in range(n):
    v,w = map(int, input().split())
    arr.append((v,w, v/w))
    
arr.sort(key=lambda x: x[2], reverse=True) # sort by value / weight

totVal = 0.0
for value, weight, ratio in arr:
    if W == 0:
        break
    if weight <= W:
        W -= weight
        totVal += value
        
    else:
        totVal += value * (W/weight)
        W = 0
        
print(f"{totVal:.1f}")