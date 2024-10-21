#include <iostream>
#include <sstream>
using namespace std;

struct Node{
    int data;
    Node* next;

    Node(int d): data(d), next(nullptr) {}
};

class Linked_List{
public:
    Node* head;
    Node* tail;
    int size;

    Linked_List(): head(nullptr), tail(nullptr), size(0) {}

    void ll_push(int d){
        Node* newNode = new Node(d);

        if(!this->tail){
            head = tail = newNode;
        }else{
            this->tail->next = newNode;
            this->tail = newNode;
        }
        size++;
    }

    string ll_print(){
        string output = "";
        Node* tmp = this->head;
        while(tmp){
            output += to_string(tmp->data) + " ";
            tmp = tmp->next;
        }
        return output;
    }
};

Node* merge(Node* list1_head, Node* list2_head){
    if(!list1_head)
        return list2_head;
    if(!list2_head)
        return list1_head;

    if(list1_head->data < list2_head->data){
        list1_head->next = merge(list1_head->next, list2_head);
        return list1_head;
    }else{
        list2_head->next = merge(list1_head, list2_head->next);
        return list2_head;
    }

    return 0;
}

Node* merge_sort(Node* list_head, int size){
    //base case
    if(size < 2)
        return list_head;

    //splitting list
    Node* second_half_head = nullptr;
    Node* tmp = list_head;

    int mid = size / 2;
    for(int i=1; i<mid; i++)
        tmp = tmp->next;

    second_half_head = tmp->next;
    tmp->next = nullptr;

    //recursively merge sort on two halves
    list_head = merge_sort(list_head, size/2);
    second_half_head = merge_sort(second_half_head, size - size/2);

    return merge(list_head, second_half_head);
}

void read_list(Linked_List& list){
    string line = "";
    getline(cin, line);

    int tmp;
    istringstream iss(line);
    while(iss >> tmp)
        list.ll_push(tmp);
}

int main(){
    Linked_List list1;
    Linked_List list2;
    read_list(list1);
    read_list(list2);

    list2.head = merge_sort(list2.head, list2.size);

    list1.head = merge(list1.head, list2.head);

    cout << list1.ll_print() << endl;

    return 0;
}