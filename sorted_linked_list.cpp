//ap assignment: 2 different approach for sorted linked list.
#include <iostream>
using namespace std;

class Node
 {
     public:
     int data;
     Node * next;
     Node(int data, Node* next) : data(data), next(next) {}
     Node() : data(0), next(nullptr) {}
 };
 class LinkedList
 {
     protected:
         Node* head;
         Node* tail;
         int size;
     public:
         LinkedList() : head(nullptr), tail(nullptr) {}
         ~LinkedList();
         virtual void pushFront(int data);
         bool popFront();
         virtual void print();
 };
 void LinkedList::pushFront(int data){
    Node * newNode = new Node(data, nullptr);
    if(head != nullptr){
        newNode->next = head;
        head = newNode; 
    }else{
        head = tail = newNode;
    } 
}

bool LinkedList::popFront() {
    if(!head){
        return 0;
    }
    Node * tmp = head;
    head = head->next;
    //is now list empty?
    if(!head)
        tail = nullptr;
    
    delete tmp;
    return 1;
}

void LinkedList::print() {
    for(Node* tmp = head; tmp; tmp = tmp->next)
        cout << tmp->data << " ";
}

LinkedList::~LinkedList(){
    Node* tmp = head;
    while(tmp){
        Node* nex = tmp->next;
        delete tmp;
        tmp = nex;
    }
}
 class SortedList1 : public LinkedList
 {
     public:
         void pushFront(int data){
            Node* newNode = new  Node(data, nullptr);

            //is empty?
            if(!head){
                head = tail = newNode;
                return;
            }
            //should be inserted in front?
            if(data < head->data){
                newNode->next = head;
                head = newNode;
                return;
            }

            Node* tmp = head;
            while(tmp->next && tmp->next->data < newNode->data){
                tmp = tmp->next;
            }
            //inserting between
            newNode->next = tmp->next;
            tmp->next = newNode;
            //is it inserted at the end?
            if(!newNode->next){
                tail = newNode;
            }
         }
 };
class SortedList2 : public LinkedList
{
    public:
        void Bsort(){
            bool swapped =false;
            do{
                swapped = false;
                Node* tmp = head;

                while(tmp->next != nullptr){
                    if(tmp->data < tmp->next->data){
                        int d = tmp->data;
                        tmp->data = tmp->next->data;
                        tmp->next->data = d;
                        swapped = true;
                    }
                    tmp = tmp->next;
                }
            }while(swapped);
        }
        void print(){
            //is empty?
            if(!head)
                return;
           Bsort();
           LinkedList::print();   
        }
};

void get_and_print(LinkedList* myList, int which){
    int in;cin>>in;
    while(in != 0){
        myList->pushFront(in);
        cin >> in;
    }
    cout << "List " << which << " : ";
    myList->print();
    cout << endl;
}

int main(){
    SortedList1 type1;
    get_and_print(&type1, 1);
    SortedList2 type2;
    get_and_print(&type2, 2);
    return 0;
}
