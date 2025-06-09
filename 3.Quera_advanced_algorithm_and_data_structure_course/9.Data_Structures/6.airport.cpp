#include <iostream>
using namespace std;

const long long INT_MAX=1000000000000;
const long long INT_MIN=-1000000000000;

class BST{
public:
    struct Node{
        long long data;
        Node* left;
        Node* right;

        Node(long long d): data(d), right(nullptr), left(nullptr){}
    };

    Node* root;
    long long size;

    BST(): root(nullptr), size(0){}

    Node* insert(Node* node, long long val){
        size++;
        if(node == nullptr){
            Node* newNode = new Node(val);
            if(this->root == nullptr)
                this->root = newNode;
            return newNode;
        }
        if(val < node->data)
            node->left = insert(node->left, val);
        else if(val > node->data)
            node->right = insert(node->right, val);

        return node;
    }

    long long upper_bound(long long val) {
        long long  res = INT_MIN;

        Node* curr = root;
        while(curr){
            if(curr->data <= val){
                res = curr->data;
                curr = curr->right;
            }else
                curr = curr->left;
        }

        return res;
    }


    long long lower_bound(long long val) {
        long long res = INT_MAX;

        Node* curr = root;
        while(curr){
            if(curr->data >= val){
                res = curr->data;
                curr = curr->left;
            }else{
                curr = curr->right;
            }
        }

        return res;
    }

    bool can_insert(long long x, long long k){
        long long lb = lower_bound(x);
        long long ub = upper_bound(x);

        return (ub+k <= x && lb-k >= x);
    }
};


int main(){
    BST* bst = new BST();
    long long q, k, x; cin >> q >> k;
    for(long long i=0; i<q; i++){
        cin >> x;
        if(bst->can_insert(x, k)){
            bst->insert(bst->root, x);
            cout << "Permission Granted!" << endl;
        }
        else   
            cout << "Permission Denied!" << endl;
    }

    return 0;
}