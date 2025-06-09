// 681C - Heap Operations 
#include<iostream>
using namespace std;

const int MAX_SIZE = 100000;

class MinHeap {
private:
    int arr[MAX_SIZE];
    int size;

    void heapify(int ind);

public:
    MinHeap() : size(0){}
    int get_size();
    bool empty();
    int parent_ind(int child_ind);
    int left_child_ind(int parent_ind);
    int right_child_ind(int parent_ind);
    void insert(int val);
    int get_min();
    int remove_min();

};

int MinHeap::get_size() { return this->size;}

bool MinHeap::empty(){ return this->size == 0;}

int MinHeap::parent_ind(int child_ind) { return (child_ind-1)/2 ;}

int MinHeap::left_child_ind(int parent_ind) { return 2*parent_ind + 1; }

int MinHeap::right_child_ind(int parent_ind) { return 2*parent_ind + 2; }

void MinHeap::insert(int val){
    arr[size] = val;
    int ind = size;
    size++;

    while(ind != 0 && arr[parent_ind(ind)] > arr[ind]){
        int tmp = arr[parent_ind(ind)];
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
        int tmp = arr[ind];
        arr[ind] = arr[min_i];
        arr[min_i] = tmp;

        heapify(min_i);
    }
}

int MinHeap::get_min(){
    if(size <= 0)
        throw runtime_error("Heap is empty");

    return arr[0];
}

int MinHeap::remove_min(){
    if(size <= 0)
        throw runtime_error("Heap is empty");

    if(size == 1){
        size--;
        return arr[0];
    } 

    int min = arr[0];
    arr[0] = arr[size-1];
    size--;
    heapify(0);

    return min;
}


int main(){
    MinHeap minH;
    string fixedOrder[2*MAX_SIZE];
    int fixedOrder_ind = 0;

    int n; cin >> n;
    for(int i=0; i<n; i++){
        string operation; cin >> operation;

        if(operation == "insert"){
            int x; cin >> x;
            minH.insert(x);
            fixedOrder[fixedOrder_ind++] = operation + " " + to_string(x);
        }
        else if(operation == "removeMin"){
            if(minH.empty()){
                minH.insert(0);
                fixedOrder[fixedOrder_ind++] = "insert 0";
            }
            minH.remove_min();
            fixedOrder[fixedOrder_ind++] = "removeMin";
        }
        else if(operation == "getMin"){
            int x; cin >> x;

            //ensure there is no value less than x in heap
            while(!minH.empty() && minH.get_min() < x){
                minH.remove_min();
                fixedOrder[fixedOrder_ind++] = "removeMin";
            }

            //x is not in heap?
            if(minH.empty() || minH.get_min() > x){
                minH.insert(x);
                fixedOrder[fixedOrder_ind++] = "insert " + to_string(x);
            }

            fixedOrder[fixedOrder_ind++] = operation + " " + to_string(x);
        }
    }

    cout << fixedOrder_ind << endl;
    for(int i=0; i<fixedOrder_ind; i++){
        cout << fixedOrder[i] << endl;
    }

    return 0;
}