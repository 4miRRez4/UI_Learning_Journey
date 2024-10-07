n, q = map(int, input().split())

sum_of_std = []
last_sum = 0
faculty_iterators = [-1 for i in range(n)]
for i in range(q):
    given = input()
    command = given.split()
    if(given[0] == "I"):
        students = int(command[1])
        last_sum = students + last_sum
        sum_of_std += [last_sum]
        
    else:
        faculty = int(command[1])
        num = int(command[2])
        it = faculty_iterators[faculty-1]
        if(it != -1):
            print(sum_of_std[it + num] - sum_of_std[it])
        else:
            print(sum_of_std[it + num])
        faculty_iterators[faculty-1] += num
        

