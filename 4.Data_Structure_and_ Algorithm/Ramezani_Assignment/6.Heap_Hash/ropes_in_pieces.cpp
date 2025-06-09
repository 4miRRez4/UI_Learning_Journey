#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

class MinHeap {
private:
    long long arr[MAX_SIZE];
    int size;

    void heapify(int ind);

public:
    MinHeap() : size(0){}
    int get_size();
    int parent_ind(int child_ind);
    int left_child_ind(int parent_ind);
    int right_child_ind(int parent_ind);
    void insert(long long val);
    long long remove_min();
};

int MinHeap::get_size() { return this->size;}

int MinHeap::parent_ind(int child_ind) { return (child_ind-1)/2 ;}

int MinHeap::left_child_ind(int parent_ind) { return 2*parent_ind + 1; }

int MinHeap::right_child_ind(int parent_ind) { return 2*parent_ind + 2; }

void MinHeap::insert(long long val){
    arr[size] = val;
    int ind = size;
    size++;

    while(ind != 0 && arr[parent_ind(ind)] > arr[ind]){
        long long tmp = arr[parent_ind(ind)];
        arr[parent_ind(ind)] = arr[ind];
        arr[ind] = tmp;

        ind = (ind-1)/2;
    }
}

void MinHeap::heapify(int ind){
    int min_i = ind;
    int left_child_i = left_child_ind(ind);
    int right_child_i = right_child_ind(ind);

    if(left_child_i < size && arr[left_child_i] < arr[min_i])
        min_i = left_child_i;

    if(right_child_i < size && arr[right_child_i] < arr[min_i])
        min_i = right_child_i;

    if(min_i != ind){
        long long tmp = arr[ind];
        arr[ind] = arr[min_i];
        arr[min_i] = tmp;

        heapify(min_i);
    }
}

long long MinHeap::remove_min(){
    if(size <= 0)
        throw runtime_error("Heap is empty");

    if(size == 1){
        size--;
        return arr[0];
    } 

    long long min = arr[0];
    arr[0] = arr[size-1];
    size--;
    heapify(0);

    return min;
}


int main(){
    int n, l;
    cin >> n;

    MinHeap ropes;
    for(int i=0; i<n; i++){
        cin >> l;
        ropes.insert(l);
    }

    long long cost=0;
    while(ropes.get_size() != 1){
        long long a = ropes.remove_min();
        long long b = ropes.remove_min();

        cost += a+b;
        ropes.insert(a+b);
    }

    cout << cost << endl;



    return 0;
}