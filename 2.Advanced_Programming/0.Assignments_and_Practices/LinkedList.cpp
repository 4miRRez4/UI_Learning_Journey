#include <iostream>
using namespace std;

class Node{
    public:
    Node(int d, Node* n=NULL, Node* p=NULL) : data(d), prev(p), next(n) {};

    Node* prev;
    int data;
    Node* next;
};

void print_list(Node* list){
    //using recursion
    if(list == NULL) return;
    cout << list->data << endl;
    print_list(list->next);
}
void print_list_nonRec(Node *list){
    //using while loop
    Node *tmp = list;
    while(tmp != NULL){
        cout << tmp->data << endl;
        tmp = tmp->next;
    }
}
void print_list_for(Node *list)
{
    //using for
    for(Node *tmp = list; tmp!=NULL; tmp = tmp->next)
        cout << tmp->data << endl;
}

void append(Node* list, int x){
    // if(list == NULL){
    //     Node *newNode = new Node(x);
    //     list = newNode;
    //     return;
    // }
    //finding the last node
    Node *last = list;
    while(last->next != NULL){
        last = last->next;
    }
    
    // Node newNode(x);
    // list->next = &newNode;
    // newNode.prev = list;
    //this is wrong. cause after this function it will be vanished in stack by compiler.
    Node *newNode = new Node(x, NULL, last);
    last->next = newNode;
}
void append_rec(Node* list, int x)
{
    if(list->next == NULL){
        Node *newNode = new Node(x, NULL, list);
        list->next = newNode;
    }else{
        append_rec(list->next, x);
    }


}

Node* create_list()
{
    return new Node(20); //dummy node(declared in heap)(compiler doesn't delete it after this function)
}

void push_front(Node*& list, int x){
    Node *newNode = new Node(x);
    newNode->next = list;
    if(list != NULL)
        list->prev = newNode;
    list = newNode;

}
void push_back(Node*& list, int x){
    Node *newNode = new Node(x);
    if(list!=NULL){
        Node *p = list;
        while(p->next != NULL)
            p = p->next;
        newNode->prev = p;
        p->next = newNode;
    }else
        list = newNode;
}
void delete_list(Node*& list){
    Node *p = list;
    while(p != NULL){
        Node *n = p;
        p = p->next;
        delete n;
    }
}
void delete_list_rec(Node *&list){
    if(list == NULL)
        return;
    delete_list_rec(list->next);
    delete list;
    list = NULL;
}

int main()
{
    Node a(10);
    Node b(3);
    Node c(4);
    a.next = &b;
    b.next = &c;
    b.prev = &a;
    c.prev = &b;

    append(&a, 45);
    print_list_nonRec(&a);


    return 0;
}