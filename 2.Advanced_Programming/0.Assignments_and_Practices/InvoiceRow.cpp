#include <iostream>
using namespace std;


class InvoiceRow{
    private:
    const char* name;
    int quantity;
    int cost;
    public:
    InvoiceRow(const char* n="Empty", int q=0, int c=0);
    ~InvoiceRow(); 
    inline void set_quantity(int q) { this->quantity = (q<=0) ? 0:q; }
    inline void set_cost(int c) { this->cost = (c<=0) ? 0:c; }
    inline void set_name(const char* n) { this->name = n; }
    inline int get_quantity() { return this->quantity; }
    inline int get_const() { return this->quantity; }
    inline const char* get_name() { return this->name; }

    int getPrice();
};
InvoiceRow::InvoiceRow(const char* n, int q, int c){
    this->cost = c;
    this->quantity = q;
    const char** a = new const char*(n);
    name = *a;
}
InvoiceRow::~InvoiceRow(){
    cout << "deconstructor of invoice row called!" << endl;
    delete name;
}
inline int InvoiceRow::getPrice(){
    return this->cost * this->quantity;
}

class Node{
    public:
    InvoiceRow* row;
    Node* next;

    Node(InvoiceRow* r, Node* next=NULL) {
        this->row = r;
        this->next = next;
    }
};

class CLinkedList{
    private:
    Node* _head;
    int size;
    Node* _tail;
    public:
    CLinkedList(int s, Node* h=NULL, Node* t=NULL){
        cout << "constructor of clinkedlist called!" << endl;
        this->size = s;
        this->_head = h;
        this->_tail = t;
    }
    ~CLinkedList(){
        cout << "deconstructor of clinkedlist called" << endl;
        size =0;
        Node* iterate = this->_head;
        while(iterate != NULL)
        {
            Node* nex = iterate->next;
            delete iterate;
            iterate = nex;
        }
        this->_head = this->_tail = NULL;
    }
    void push_front(InvoiceRow* newRow){
        Node* newNode = new Node(newRow);
        newNode->next = this->_head;
        this->_head = newNode;
        if(this->_tail == nullptr)
            this->_tail = newNode;
        this->size++;
    }
    void push_back(InvoiceRow* newRow){
        if(this->_head == nullptr){
            // Node* newNode = new Node(newRow);
            // this->head = newNode;
            // this->tail = newNode;
            this->push_front(newRow);
        }
        else{
            Node* newNode = new Node(newRow);
            this->_tail->next = newNode;
            this->_tail = newNode;
            this->size++;
        }
    }
    void print_list(){
        if(this->size != 0){
            Node * tmp = this->_head;
            while(tmp->next != NULL)
            {
                cout << "quantity, cost, name: ";
                cout << tmp->row->get_quantity() << ", " << tmp->row->get_const() << ", " << tmp->row->get_name() << endl;
                tmp = tmp->next;
            }
        }else
            cout << "this list is empty!!!" << endl;
    }
    void pop_front(){
        Node* tmp = this->_head;
        this->_head = this->_head->next;
        if(this->size == 1)
            this->_tail = nullptr;
        this->size--;
        delete tmp;
    }
};

class Invoice{
    private:
    int invoiceNum;
    CLinkedList* rowList;
    public:
    Invoice(int num, CLinkedList* list){
        this->invoiceNum = num;
        this->rowList = list;
    }
    ~Invoice(){
        this->rowList.~CLinkedList();
    }
    void addRow(const char* n, int q, int c){
        InvoiceRow tmpRow(n, q, c);
        this->rowList->push_back(tmpRow);
    }
    int getTotalPrice(){
        int totalPrice =0;
        Node* tmp = this->rowList->_head;
        while(tmp){
            totalPrice += tmp->row->getPrice();
        }
        return totalPrice;
    }
    Invoice* operator=(const Invoice& other){
        this->invoiceNum = other.invoiceNum;
        this->rowList = other.rowList;
    }
};

int main()
{
    InvoiceRow row1("rob", 1, 50000);
    cout << row1.get_name() << endl;
    row1.set_quantity(3);
    cout << row1.getPrice() << endl;


    return 0;
}