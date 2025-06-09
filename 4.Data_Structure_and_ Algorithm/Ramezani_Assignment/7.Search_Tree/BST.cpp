#include <iostream>
using namespace std;

class BST{
    struct Node
    {
        int val;
        Node* left_child;
        Node* right_child;

        Node(int v): val(v), left_child(nullptr), right_child(nullptr){}
    };


public:
    Node* root;
    BST(): root(nullptr){}

    Node* insert(Node* n, int newVal){
        if(root == nullptr){
            root = new Node(newVal);
            return root;
        }
        
        if(n == nullptr)
            return new Node(newVal);

        if(newVal > n->val)
            n->right_child = insert(n->right_child, newVal);
        else if(newVal < n->val)
            n->left_child = insert(n->left_child, newVal);

        return n;
    }

    Node* clear(Node* n){
        if(n == nullptr) return nullptr;

        clear(n->left_child);
        clear(n->right_child);
        
        delete n;
        return nullptr;
    }

    Node* find_min(Node* n){
        while(n && n->left_child)
            n = n->left_child;
        return n;
    }

    Node* find_max(Node* n){
        while (n && n->right_child)
            n = n->right_child;
        return n;   
    }

    Node* remove(Node* n, int val){
        if(val < n->val)
            n->left_child = remove(n->left_child, val);
        if(val > n->val)
            n->right_child = remove(n->right_child, val);
        else{
            Node* alter;
            if(n->left_child == nullptr){
                alter = n->right_child;
                delete n;
                return alter;
            }
            if(n->right_child == nullptr){
                alter = n->left_child;
                delete n;
                return alter;
            }

            //has two child
            alter = find_min(n->right_child);
            n->val = alter->val;
            n->right_child = remove(n->right_child, alter->val);
        }
        return n;
    }

    Node* find(Node* n, int val){
        if(n == nullptr || n->val == val)
            return n;
        if(val > n->val)
            return find(n->right_child, val);
        return find(n->left_child, val);
    }

    void k_smallest_inorder(Node* n, int& k, int& res){
        if(!n) return;

        k_smallest_inorder(n->left_child, k, res);

        //visiting k'th smallest
        k--;
        if(k == 0){
            res = n->val;
            return;
        }

        k_smallest_inorder(n->right_child, k, res);
    }
    
};

int main(){
    int n, k, newVal; cin >> n >> k;

    BST* myBst = new BST();
    for(int i=0; i<n; i++){
        cin >> newVal;
        myBst->insert(myBst->root, newVal);
    }

    int res = 0;
    myBst->k_smallest_inorder(myBst->root, k, res);
    cout << res << endl;

    return 0;
}