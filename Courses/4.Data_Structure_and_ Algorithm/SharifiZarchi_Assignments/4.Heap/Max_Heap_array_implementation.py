def parent_idx(i):
    return i//2

def leftChild_idx(i):
    return 2*i +1

def rightChild_idx(i):
    return 2*i +2

class Max_Heap:
    def __init__(self):
        self.heap = []

    def get_size(self):
        return len(self.heap)
    
    def bubble_up(self, idx):
        while(idx > 0 and self.heap[parent_idx(idx)] < self.heap[idx]):
            self.heap[idx], self.heap[parent_idx(idx)] = self.heap[parent_idx(idx)], self.heap[idx]
            idx = parent_idx(idx)

    def bubble_down(self, idx):
        while(leftChild_idx(idx) <= self.get_size()-1):
            newIdx = idx
            if(self.heap[leftChild_idx(idx)] > self.heap[newIdx]):
                newIdx = leftChild_idx(idx)
            if(rightChild_idx(idx) < self.get_size() and self.heap[rightChild_idx(idx)] > self.heap[newIdx]):
                newIdx = rightChild_idx(idx)

            if(idx == newIdx):
                break

            self.heap[idx], self.heap[newIdx] = self.heap[newIdx], self.heap[idx]
            idx = newIdx

    def insert(self, item):
        self.heap.append(item)
        self.bubble_up(self.get_size()-1)

    def get_max(self):
        if(self.get_size() == 0):
            raise Exception("Heap is empty!")
        return self.heap[0]
    
    def del_max(self):
        if(self.get_size() == 0):
            raise Exception("Heap is empty!")
        
        max = self.heap[0]
        self.heap[0] = self.heap[-1]
        del(self.heap[-1])
        self.bubble_down(0)

        return max
    
    def build_heap_with_bu(self, list):
        self.heap = list
        for i in range(self.get_size()):
            self.bubble_up(i)


    def build_heap_with_bd(self, list):
        self.heap = list
        for i in range(self.get_size()-1, -1, -1):
            self.bubble_down(i)

    def clear(self):
        self.heap = []


if __name__ == "__main__":
    heap = Max_Heap()
    heap.build_heap_with_bd([1, 2, 3, 4, 5])
    print(heap.heap)
    print (heap.del_max())
    print(heap.heap)
    heap.insert(8)
    print(heap.heap)
    print (heap.del_max())
    print (heap.del_max())
    print (heap.del_max())
    print (heap.del_max())
    print(heap.heap)
    print (heap.get_size())