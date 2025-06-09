#include <iostream>
using namespace std;

class Node {
public:
    Node(int d, Node *n = NULL, Node *p = NULL) 
        : data(d), next(n), prev(p) {}

    int data;
    Node *next;
    Node *prev;
};

class List{
    public:
    List();
    ~List();
    void print();
    void push_front(int x);
    void push_front_list(List* l);
    void push_back(int x);
    Node* head() { return _head;}
    Node* last() { return _last;}
    void clear();
    Node* find(int x);
    void insert_after(Node* p, int x);
    bool isThere(int key);
    bool isThere_rec(Node* p, int key);
    private:
    Node* _head;
    Node* _last;
    Node* find_rec(Node* p, int x);
};
List::List(){
    _head = NULL;
    _last = NULL;
}
void List::print(){
    for(Node *p = _head; p!=NULL; p = p->next)
        cout << p->data << ' '; 
}
void List::push_front(int x){
    Node *newNode = new Node(x);
    newNode->next = _head;
    if(_head != NULL)
        _head->prev = newNode;
    _head = newNode;
    if(_last == NULL)
        _last = newNode;
}
void List::push_back(int x){
    if(_head == NULL)
        push_front(x);
    else{
        Node *newNode = new Node(x);
        newNode->prev = _last;
        _last->next = newNode;
        _last = newNode;
    }
}
List::~List(){
    clear();
}
void List::clear(){
    Node *p = _head;
    while(p!=NULL){
        Node* q = p;
        p = p->next;
        delete q;
    }
    _head = NULL;
    _last = NULL;
}
Node* List::find(int x){
    return find_rec(_head, x);
}
Node* List::find_rec(Node *p, int x){
    if(p == NULL)
        return NULL;
    if(p->data == x)
        return p;
    return find_rec(p->next, x);
}
void List::insert_after(Node* p, int x){
    Node* newNode = new Node(x);
    newNode->prev = p;
    newNode->next = p->next;  
    p->next = newNode;
    if(newNode->next!=NULL)
        p->next->prev = newNode;
    else
        _last = newNode;

}
bool List::isThere(int key){
    for(Node* tmp=_head; tmp!=NULL; tmp = tmp->next)
        if(tmp->data == key)
            return true;
    return false;
}
bool List::isThere_rec(Node* p, int key){
    if(p == NULL)
        return false;
    if(p->data == key)
        return true;
    isThere_rec(p->next, key);
}
void List::push_front_list(List* l){
    for(Node* p = l->head(); p!=NULL; p = p->next)
        push_front(p->data);
}

int main(){
    List l;
    
    l.push_back(86);
    l.push_front(43);
    l.push_front(12);
    
    l.print();
    cout << endl;

    int sum = 0;
    for (Node* p = l.head(); p != NULL; p = p->next)
        sum += p->data;        
    cout << sum << endl;


    List l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    return 0;
}