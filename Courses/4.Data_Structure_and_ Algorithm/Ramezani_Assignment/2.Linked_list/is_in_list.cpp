#include <iostream>
#include <sstream>
using namespace std;

struct Node{
    int data;
    Node* next;

    Node(int d): data(d), next(nullptr) {}
};

class LinkedList{
public:
    Node* head;
    Node* tail;

    LinkedList(): head(nullptr), tail(nullptr) {}

    void push(int d){
        Node* newNode = new Node(d);

        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
    }
};


bool is_in_list(LinkedList& list1, LinkedList& list2){
    Node* list2_n = list2.head;

    while(list2_n != nullptr){
        Node* list1_it = list1.head;
        Node* list2_it = list2_n;

        while(list1_it != nullptr && list2_it != nullptr && list1_it->data == list2_it->data){
            list1_it = list1_it->next;
            list2_it = list2_it->next;
        }

        if(list1_it == nullptr) return true;

        list2_n = list2_n->next;
    }

    return false;
}
void read_list(LinkedList& list){
    string line;
    getline(cin, line);
    istringstream iss(line);
    int n;
    while(iss >> n)
        list.push(n);
}

int main(){
    LinkedList list1;
    LinkedList list2;

    read_list(list1);
    read_list(list2);

    if(is_in_list(list1, list2))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}