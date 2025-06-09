#include <iostream>
using namespace std;

const int MAX_SIZE = 500;

template<typename T>
class Queue{
public:
    T q[MAX_SIZE];
    int front;
    int back;
    int size;

    Queue(): front(0), back(0){}

    void enqueue(T val){
        q[back] = val;
        back = (back+1) % MAX_SIZE;
        size++;
    }

    T dequeue(){
        T tmp = q[front];
        front = (front+1) % MAX_SIZE;
        size--;
        return tmp;
    }

    T Front(){ return q[front];}

    T Back(){ return q[back];}

    int Size(){ return size;}
};

int main(){
    Queue<int>* players = new Queue<int>();
    int n; cin >> n;
    for(int i=1; i<=n; i++){
        players->enqueue(i);
    }

    int k; cin >> k;
    while(players->Size() != 1){
        for(int i=0; i<k-1; i++){
            int tmp = players->Front();
            players->dequeue();
            players->enqueue(tmp);            
        }
        players->dequeue();
    }
    cout << players->Front() << endl;

    return 0;
}