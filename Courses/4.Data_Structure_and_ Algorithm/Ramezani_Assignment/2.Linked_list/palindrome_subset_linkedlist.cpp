#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node* prev;

    Node(int d){
        this->data = d;
        this->next = NULL;
        this->prev = NULL;
    }
};

class Doubly_Linked_List{
public:
    Node* header;
    Node* trailer;

    Doubly_Linked_List(){
        this->header = new Node(-1);
        this->trailer = new Node(-1);
        this->header->next = trailer;
        this->trailer->prev = header;
    }

    void push(int d){
        Node* newNode = new Node(d);

        newNode->prev = trailer->prev;
        trailer->prev->next = newNode;
        newNode->next = trailer;
        trailer->prev = newNode;
    }

    // string print_list(){
    //     string list = "";
    //     Node* tmp = header->next;
    //     while(tmp != trailer){
    //         list += to_string(tmp->data) + " ";
    //         tmp = tmp->next;
    //     }
    //     list += "\n";
    //     return list;
    // }

};

int is_subset_palindrome(Node* left, Node* right){
    int l = 0;
    while((left != right) && (right->next != left)){
        if(left->data != right->data)
            return 0;

        l+=2;
        left = left->next;
        right = right->prev;
    }
    if(left == right)
        l++;

    return l;
}

int check_subsets_for_longest_pal(Doubly_Linked_List& ddl){
    int max_len = 0;
    for(Node* left = ddl.header->next; left != ddl.trailer->prev; left = left->next){
        for(Node* right = ddl.trailer->prev; right != left; right = right->prev){
            int len = is_subset_palindrome(left, right);
            if(len != 0){
                if(max_len < len)
                    max_len = len;
                break;
            }
        }
    }
    return max_len;
}

//TODO: expend around element

int main(){
    string answer = "";
    int n; cin >> n;
    for(int i=0; i<n; i++){
        Doubly_Linked_List ddl;

        int m; cin >> m;
        for(int j=0; j<m; j++){
            int tmp; cin >> tmp;
            ddl.push(tmp);
        }
        answer += to_string(check_subsets_for_longest_pal(ddl));
    }
    cout << answer;
    return 0;
}