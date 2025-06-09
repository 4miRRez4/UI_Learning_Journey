#pycity first exercise
#getting different kinds of weight from input and returning closest sum of weights to 1000;

#getting input
weights = []
weightKinds = int(input())
for w in range(weightKinds):
    weights.append(int(input()))

#calculating different subsets of weights and compare them to closest to 1000
closest = 0
length = len(weights)
for l in range(1,length+1):#iterating on length(subsets with different lengthes);
    for s in range(length):#iterating for start(going forward on list);
        tmp = 0
        for i in range(l):#iterating for making tmp;
            tmp += (weights[(s+i)%length])
        if(abs(tmp-1000) == abs(1000-closest)):
            if(tmp>closest):
                closest=tmp

        if(abs(tmp-1000) < abs(1000-closest)):
            closest = tmp

print(closest)

