#include <iostream>
#include <queue>
using namespace std;

const int MAX_SIZE = 200000;

class stackque{
public:
    int sq[MAX_SIZE];
    int front;
    int back;
    int size;
    
    stackque(): front(0), back(0), size(0){}

    int get_front(){
        if(size == 0)
            return 0;
        return sq[front];
    }

    int get_back(){
        if(size == 0)
            return 0;
        return sq[(back-1 +MAX_SIZE) % MAX_SIZE];
    }

    bool is_empty() { return size==0; }
    void push_back(int val){
        sq[back] = val;
        back = (back + 1) % MAX_SIZE;
        size++;
    }

    void pop_back(){
        if(size == 0)
            return;
        back = (back-1 + MAX_SIZE) % MAX_SIZE;
        size--;
    }

    void push_front(int val){
        front = (front-1 + MAX_SIZE) % MAX_SIZE;
        sq[front] = val;
        size++;
    }

    void pop_front(){
        if(size == 0)
            return;
        front = (front+1) % MAX_SIZE;
        size--;
    }
};

int main(){
    int n, k, tmp; cin >> n >> k;
    int nums[n+k-1] = {};
    for(int i=0; i<n+k-1; i++){
        cin >> tmp;
        nums[i] = tmp;
    }
    
    stackque* decreasing_max_ind = new stackque();
    for(int i=0; i<n+k-1; i++){
        while(!decreasing_max_ind->is_empty() && nums[decreasing_max_ind->get_back()] <= nums[i])
            decreasing_max_ind->pop_back();
        
        decreasing_max_ind->push_back(i);

        if(!decreasing_max_ind->is_empty() && decreasing_max_ind->get_front() < i-k+1)
            decreasing_max_ind->pop_front();

        if(i>=k-1){
            cout << nums[decreasing_max_ind->get_front()] << " ";
        }
    }


    return 0;
}