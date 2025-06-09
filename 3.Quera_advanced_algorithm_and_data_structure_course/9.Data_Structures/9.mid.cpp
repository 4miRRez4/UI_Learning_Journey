#include <iostream>
#include <queue>
using namespace std;

int main(){
    priority_queue<int> lessThanEqual_maxHeap;
    priority_queue<int, vector<int>, greater<int>> greaterThan_minHeap;

    int n;
    for(int i=0; i<n; i++){
        int newVal; cin >> newVal;

        int prevMax = lessThanEqual_maxHeap.top();
        lessThanEqual_maxHeap.push(newVal);
        int updatedMax = lessThanEqual_maxHeap.top();

        if(updatedMax != prevMax){
            //Complete
        }
        lessThanEqual_maxHeap.top();
        lessThanEqual_maxHeap.pop();
    }

    return 0;
}
//TODO: one heap: each time insert and delete root and erplace with root.right().leftMost()
