order = input()

opens_stack = []
for i in range(len(order)):
    if(order[i] == '(' or order[i] == '['):
        opens_stack.append(order[i])
    elif(order[i] == ')'):
        if(opens_stack.pop() != '('):
            raise Exception("Invalid Order!!!")
    elif(order[i] == ']'):
        if(opens_stack.pop() != '['):
            raise Exception("Invalid Order!!!")
        
print("Valid.")