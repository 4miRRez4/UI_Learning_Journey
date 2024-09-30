#second assignment for psycity
#https://quera.org/course/assignments/65689/problems/223182

def permutations(arr):
    if len(arr) == 0:
        return [[]]
    
    result = []
    for i in range(len(arr)):
        first_element = arr[i]
        remaining_elements = arr[:i] + arr[i+1:]
        for perm in permutations(remaining_elements):
            result.append([first_element] + perm)
    
    return result

def sum_of_cash(arr, bankClosingTime):
    cash = 0
    timePassed = 0
    for tup in arr:
        personPucket = tup[0]
        timeOfPerson = tup[1]
        if(timeOfPerson >= timePassed and bankClosingTime-timePassed >= timeOfPerson):
            cash += personPucket
            timePassed+=1

    return cash

#getting input
numberOfPeople, bankTime = [int(x) for x in input().split()]
person=[] 
for i in range(numberOfPeople):
    cash, timeToLeave = map(int, input().split())
    person.append((cash, timeToLeave))

#calculating different subsets of person array
subsetsOfPeople = []
for l in range(1,numberOfPeople+1):#iterating for different subset length
    for s in range(numberOfPeople):#iterating for start(going forward on list);
        tmpPeople = []
        for i in range(l):#adding elements from s(start) to l(length) people ahead of it to tmp
            tmpPeople.append(person[(s+i)%numberOfPeople])

        subsetsOfPeople.append(tmpPeople)

#calculating different permutations of subsets and summing up considering time condition
maxCash = 0
for subset in subsetsOfPeople:
    perms = permutations(subset)
    for perm in perms:
        sumOfPerm =sum_of_cash(perm,bankTime)
        if(sumOfPerm > maxCash):
            maxCash = sumOfPerm
print(maxCash)


        
