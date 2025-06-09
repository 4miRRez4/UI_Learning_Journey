#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T val;
    Node* next;
    Node(T v): val(v), next(nullptr) {}
};

template<typename T>
class LinkedQueue{
public:
    Node<string>* head;
    Node<string>* tail;

    LinkedQueue(): head(nullptr), tail(nullptr) {}

    void enqueue(T val){
        Node<string>* newNode = new Node(val);
        if(tail == nullptr)
            head = tail = newNode;
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    Node<string>* dequeue(){
        if(head == nullptr)
            throw exception();
        else{
            Node<string>* front = head;
            if(tail == head)
                head = tail = nullptr;
            else
                head = head->next;
            return front;
        }
       return 0; 
    }
};

int main(){
    int n; cin >> n;
    LinkedQueue<string>* lq = new LinkedQueue<string>();

    lq->enqueue("1");
    int i=0;
    for(i; i<n/2; i++){
        string front = lq->dequeue()->val;
        lq->enqueue(front+"0");
        lq->enqueue(front+"1");
        cout << front << endl;
    }

    try{
        for(i; i<n; i++)
            cout << lq->dequeue()->val << endl;
    }catch(exception e){
        
    }
    return 0;
}