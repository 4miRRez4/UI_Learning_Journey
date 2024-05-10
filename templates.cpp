// #include <iostream>
// using namespace std;

// template<typename T>
// class Cell{
// public:
//     Cell(T d) : data(d) {}
//     T get_value() const;
//     void set_value(T x);
// private:
//     T data;
// };
// template<typename T>
// T Cell<T>::get_value() const {
//     return data;
// }
// template<typename T>
// void Cell<T>::set_value(T x){
//     data = x;
// }

// int main()
// {
//     Cell<int> a(10);
//     a.set_value(12);
//     cout << a.get_value() << endl;

//     string s = "JJ";
//     Cell<string> b(s);
//     cout << b.get_value() << endl;

//     return 0;
// }


// template<typename U, typename V> 
// class Pair {
// public:
//     Pair(U f, V s) : first(f), second(s) {}
//     U get_first() { return first; }
//     V get_second() { return second; }
// private:
//     U first;
//     V second;
// };

// int main()
// {
//     Pair<string, double> record("gholam", 11.4);
//     cout << record.get_first();
// }

// template<typename T>
// void print_array(T a[], int n) {
//     for (int i = 0; i < n; i++)
//         cout << a[i] << ' ';
// }

// int main()
// {
//     int a[3] = {1, 3, 4};
//     char c[2] = {'b', 'a'};
    
//     print_array<int>(a, 3);
//     print_array<char>(c, 2);    

//     print_array(a, 3);
//     print_array(c, 2);
// }

// #include <iostream>
// #include <vector>
// #include <cstdlib>
// using namespace std;

// class queue_operation_exception {};

// template<typename T, int S> class queue {
// public:
//     queue() { count = 0; }
//     void enqueue(T x);
//     T dequeue();
//     int size() const { return elements.size(); }
// private:
//     T elements[S];
//     int count;
// };

// template<class T, int S>
// void queue<T, S>::enqueue(T x)
// {
//     if (count >= sizeof(elements))
//         throw queue_operation_exception();
//     elements[count++] = x;
// }

// template<class T, int S>
// T queue<T, S>::dequeue() 
// {
//     if (count == 0)
//         throw queue_operation_exception();
//     T result = elements[0];
//     for (int i = 1; i < count; i++)
//         elements[i-1] = elements[i];
//     count--;
//     return result;
// }

// int main() {
//     queue<int, 10> q;
//     q.enqueue(10);
//     q.enqueue(20);
//     cout << q.dequeue() << endl;

//     queue<string, 8> p;
//     p.enqueue("salaam");
//     p.enqueue("chetori?");
//     cout << p.dequeue() << endl;    
// }

#include <iostream>
using namespace std;

template<typename T>
class List {
private:
    class Node {
    public:
        Node(T d, Node *n = NULL, Node *p = NULL) 
            : data(d), next(n), prev(p) {}

        T data;
        Node *next;
        Node *prev;
    };

public:
    class Iterator {
    public:
        T next_element() { 
            T to_be_returned = current->data;
            current = current->next;
            return to_be_returned;
        }
        bool has_more_elements() {
            return current != NULL;
        }
    private:
        Node *current;
        Iterator(Node* n) { current = n; }
        friend class List;
    };

public:
    List();
    ~List();
    void print();
    void push_front(T x);
    void push_back(T x);
    Iterator get_iterator() {
        return Iterator(_head);
    }
private:
    Node* _head;
    Node* _last;
};

template<typename T>
List<T>::List() {
    _head = NULL;
    _last = NULL;
}

template<typename T>
void List<T>::print() {
    for (Node* p = _head; p != NULL; p = p->next) {
        cout << p->data << ' ';
    }
}

template<typename T>
void List<T>::push_front(T x) {
    Node *new_node = new Node(x);
    new_node->next = _head;
    if (_head != NULL)
        _head->prev = new_node;
    _head = new_node;
    if (_last == NULL)
        _last = new_node;
}

template<typename T>
void List<T>::push_back(T x) {
    if (_head == NULL)
        push_front(x);
    else {
        Node *new_node = new Node(x);
        new_node->prev = _last;
        _last->next = new_node;
        _last = new_node;
    }
}

template<typename T>
List<T>::~List() {
    Node *p = _head;
    while (p != NULL) {
        Node *q = p;
        p = p->next;
        delete q;
    }
    _head = NULL;
}

int main() {
    List<int> l;
    
    l.push_back(86);
    l.push_front(43);
    l.push_front(12);
    
    l.print();
    cout << endl;

    int sum = 0;
    
    List<int>::Iterator it = l.get_iterator();
    while (it.has_more_elements())
        sum += it.next_element();
        
    cout << sum << endl;
}
