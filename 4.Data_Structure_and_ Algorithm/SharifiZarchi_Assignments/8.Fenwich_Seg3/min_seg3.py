class Min_Segment_Tree:
    def __init__(self, arr):
        self.n = len(arr)
        self.l = [0] * (4 * self.n + 4) 
        self.r = [0] * (4 * self.n + 4) 
        self.lazy=[float("inf")] * (4 * self.n + 4) 
        self.min=[float("inf")] * (4 * self.n + 4) 
        self.make_tree(arr, 0, self.n, 1)
        
    def make_tree(self, arr, l, r, ind):
        self.l[ind] = l 
        self.r[ind] = r
        if r <= l + 1:
            self.min[ind] = arr[l]
            return
        mid = (l + r) // 2
        self.make_tree(arr, l, mid, 2 * ind)
        self.make_tree(arr, mid, r, 2 * ind + 1)
        self.min[ind] = min(self.min[2 * ind], self.min[2 * ind + 1])
        
    def propagate_lazy(seg3, ind, l, r):
        seg3.min[ind] = min(seg3.min[ind], seg3.lazy[ind])
        seg3.lazy[2*ind] = min(seg3.lazy[2 * ind], seg3.lazy[ind])
        seg3.lazy[2*ind+1] = min(seg3.lazy[2 * ind + 1], seg3.lazy[ind])
        seg3.lazy[ind] = float("inf")

    def update(seg3, st, e, v, ind=1):
        l = seg3.l[ind]
        r = seg3.r[ind]
        seg3.propagate_lazy(ind, l, r)
        if(r <= st or l >= e): #No overlap
            return
        if(r <= e and l >= st): #Full overlap
            seg3.lazy[2*ind] = min(seg3.lazy[2*ind], v)
            seg3.lazy[2*ind+1] = min(seg3.lazy[2*ind+1], v)
            seg3.min[ind] = min(seg3.min[ind], v)
            return
        #Segments have intersection
        seg3.update(st, e, v, 2*ind)
        seg3.update(st, e, v, 2*ind+1)
        seg3.min[ind] = min(seg3.min[2*ind], seg3.min[2*ind+1])
        

    def get_min(seg3, st, e, ind=1):
        l = seg3.l[ind]
        r = seg3.r[ind]
        seg3.propagate_lazy(ind, l, r)
        if(r <= st or l >= e): #No overlap
            return float("inf")
        if(l >= st and r <= e): #Full overlap
            return seg3.min[ind]
        #Segments have intersection
        return min(seg3.get_min(st, e, 2*ind), seg3.get_min(st, e, 2*ind+1))
    
segment_tree = Min_Segment_Tree([1, 2, 3, 4, 5, 6, 7, 8])
print(segment_tree.get_min(2, 5))
segment_tree.update(2, 4, 3)
print(segment_tree.get_min(2, 5))