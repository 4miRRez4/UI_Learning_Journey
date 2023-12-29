lst = ['a','b','c']
out = []
length =len(lst)
for l in range(1,length+1):#iterating on length(subsets with different lengthes);
    for s in range(length):#iterating for start(going forward on list);
        tmp = ""
        for i in range(l):#iterating for making tmp;
            tmp += lst[(s+i)%length]
        
        out.append(tmp)
        if l!=1:
            out.append(tmp[::-1])

print(out)
        


