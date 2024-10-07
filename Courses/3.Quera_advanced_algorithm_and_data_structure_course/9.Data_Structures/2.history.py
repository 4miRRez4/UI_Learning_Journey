q = int(input())
curr_str = ""
history = []
for c in range(q):
    command = input().split()
    if(command[0] != "undo"):
        ind = int(command[1])-1
        history.append(curr_str)
        
    match command[0]:
        case "insert":
            curr_str = curr_str[:ind] + command[2] + curr_str[ind:]
        case "delete":
            curr_str = curr_str[:ind] + curr_str[ind+1:]
        case "undo":
            curr_str = history.pop()
            
    
print(curr_str)
