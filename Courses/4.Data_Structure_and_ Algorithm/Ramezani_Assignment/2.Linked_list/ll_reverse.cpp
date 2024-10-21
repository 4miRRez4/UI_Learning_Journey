#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node* prev;

    Node(int d) : data(d), next(nullptr), prev(nullptr) {}
};

class DLL{
public:
    Node* head;
    Node* tail;

    DLL() : head(nullptr), tail(nullptr) {}

    void DDL_push(int d){
        Node* newNode = new Node(d);

        //is list empty?
        if(head == nullptr){
            this->head = newNode;
            this->tail = newNode;
        }else{
            this->tail->next = newNode;
            newNode->prev = this->tail;
            this->tail = newNode;
        }
    }

    int DDL_get_data(int n, int idx){
        Node* curr;
        if(idx <= n/2){
            int i = 1;
            curr = this->head;
            while(curr != nullptr && i < idx){
                curr = curr->next;
                i++;
            }
        }else{
            int i=n;
            curr = this->tail;
            while(curr != nullptr && i > idx){
                curr = curr->prev;
                i--;
            }
        }

        if(curr == nullptr)
            return -1;
        else
            return curr->data;
    }

    void DDL_reverse(int n, int i, int j){
        Node* left;
        Node* right;

        if(i < n/2){
            left = this->head;
            int p=1;
            while(p < i){
                left = left->next;
                p++;
            }

            if(j-i < n-j){
                right = left;
                while(p < j){
                    right = right->next;
                    p++;
                }
            }else{
                right = this->tail;
                p = n;
                while(p > j){
                    right = right->prev;
                    p--;
                }
            }

        }else{
            right = this->tail;
            int p = n;
            while(p > j){
                right = right->prev;
                p--;
            }

            left = right;
            while(p > i){
                left = left->prev;
                p--;
            }
        }

        while(left != right && left->prev != right){
            if(left->next != nullptr) left->next->prev = right;
            if(left->prev != nullptr) left->prev->next = right;
            if(right->next != nullptr) right->next->prev = left;
            if(right->prev != nullptr) right->prev->next = left;

            Node* tmp = left->next;
            left->next = right->next;
            right->next = tmp;

            tmp = left->prev;
            left->prev = right->prev;
            right->prev = tmp;

            if(this->head == left) this->head = right;
            if(this->tail == right) this->tail = left;

            left = left->next;
            right = right->prev;
        }
    }

    void DDL_reverse2(int n, int i, int j){
        Node* curr;
        int c;
        if(i <= n/2){
            curr = this->head;
            c = 1;
            while(curr != nullptr && c<i){
                curr = curr->next;
                c++;
            }  
        }else{
            curr = this->tail;
            c = n;
            while(curr != nullptr && c>i){
                curr = curr->prev;
                c--;
            }
        }

        Node* last;
        Node* first = curr;
        Node* first_prev = curr->prev;
        while(curr != nullptr && c<=j){
            Node* curr_next = curr->next;
            curr->next = curr->prev;
            curr->prev = curr_next;

            if(c == j)
                last = curr;

            curr = curr_next;
            c++;
        }

        if(first == this->head){
            this->head = last;
        }else{
            first->next = curr;
            first_prev->next = last;
        }

        if(last == this->tail){
            this->tail = first;
        }else{
            last->prev = first_prev;
            curr->prev = first;
        }
    }
};


int main(){
    int n; cin >> n;

    DLL my_dll;
    for(int i=1; i<=n; i++)
        my_dll.DDL_push(i);

    int m; cin >> m;
    for(int p=0; p<m; p++){
        string operation; cin >> operation;
        switch(operation[0]){
            case 'N':
                int k; cin >> k;
                cout << my_dll.DDL_get_data(n, k) << endl;
                break;

            case 'R':
                int i, j; cin >> i >> j;
                my_dll.DDL_reverse2(n, i, j);
                break;
        }
    }

    return 0;
}