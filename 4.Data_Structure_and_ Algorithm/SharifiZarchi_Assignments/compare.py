from matplotlib.pyplot import *
import timeit
def get_time(f, input):
    start = timeit.default_timer()
    f(input)
    stop = timeit.default_timer()
    return (stop - start) * 1000 * 1000 #microseconds

def get_avg_time(f, input):
    res = 1 << 30 #inf
    s = 10
    r = 5
    for i in range(s):
        sum = 0
        for j in range(r): 
            sum += get_time(f, input)
        res = min(res, sum / float(r))
    return res

def plot1(N, numbers):
    figure(figsize=(20, 10))
    xlabel("Size of input (n)")
    ylabel("Time")
    y = [get_avg_time(heap.build_heap_with_bubble_up, a) for a in numbers]
    plot(N, y, 'r', label='build heap with bubble down',linewidth=5)
    y = [get_avg_time(heap.build_heap_with_bubble_down, a) for a in numbers]
    plot(N, y, 'b', label='build heap with bubble up',linewidth=5)
    legend(loc=2)
    
from random import randrange
max_N = 30000
N = [1, 5] + list (range(100, max_N, 5000))
numbers = [[randrange(100000) for j in range(i)] for i in N]
plot1(N, numbers)