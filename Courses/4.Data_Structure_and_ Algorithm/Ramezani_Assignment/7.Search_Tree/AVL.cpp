#include <iostream>
using namespace std;


class AVLTree{
private:
    struct BSTNode{
        int val;
        int height;
        BSTNode* parent;
        BSTNode* left_child;
        BSTNode* right_child;

        BSTNode(int v, BSTNode* p=nullptr, BSTNode* l=nullptr, BSTNode* r=nullptr, int h=0): val(v), parent(p), left_child(l), right_child(r), height(h) {}
    };

    BSTNode* root;
    BSTNode* dummy;

    int height(BSTNode* n){ return n != dummy ? n->height : 0; }

    int getBalance(BSTNode* n){ return n != dummy ? height(n->left_child) - height(n->right_child) : 0; }

    bool isBalanced(BSTNode* n){ return getBalance(n) <= 1; }

    void recomputeHeight(BSTNode* n){ if(n != dummy) n->height = 1 + max(height(n->left_child), height(n->right_child)); }

    void relink(BSTNode* parent, BSTNode* child, bool makeLeftChild){
        if(child != dummy)  child->parent = parent;
        if(makeLeftChild)
            parent->left_child = child;
        else
            parent->right_child = child;
    }


    void rotate(BSTNode* p){
        BSTNode* x = p;
        BSTNode* y = x->parent;
        BSTNode* z = y->parent;

        if(z == nullptr){
            root = x;
            x->parent = nullptr;
        }
        else
            relink(z, x, y == z->left_child);

        if(x == y->left_child){
            relink(y, x->right_child, true);
            relink(x, y, false);
        }
        else{
            relink(y, x->left_child, false);
            relink(x, y, true);
        }
    }

    BSTNode* restructure(BSTNode* p){
        BSTNode* x = p;
        BSTNode* y = x->parent;
        BSTNode* z = y->parent;

        if((x == y->right_child) == (y == z->right_child)){
            rotate(y);
            return y;
        }
        else{
            rotate(x);
            rotate(x);
            return x;
        }
    }

    BSTNode* tallerChild(BSTNode* n){
        if(n->left_child->height > n->right_child->height)
            return n->left_child;

        if(n->left_child->height < n->right_child->height)
            return n->right_child;

        if(this->root == n) return n->left_child; //or right_child, doesn't matter.
        
        //equal height children
        if(n == n->parent->left_child) 
            return n->left_child;
        else 
            return n->right_child;
    }
    
    void rebalance(BSTNode* n){
        int oldHeight, newHeight;
        do{
            oldHeight = n->height;
            if(!isBalanced(n)){
                n = restructure(tallerChild(tallerChild(n)));

                recomputeHeight(n->left_child);
                recomputeHeight(n->right_child);
            }

            recomputeHeight(n);
            newHeight = n->height;

            n = n->parent;
        }while(oldHeight != newHeight && n != nullptr);
    }

    BSTNode* findMax(BSTNode* n){
        while(n->right_child != dummy) n = n->right_child;
        return n;
    }

    void deleteNode(BSTNode* n){
        if(n->left_child == dummy && n->right_child == dummy){
            if(n->parent){
                relink(n->parent, dummy, n == n->parent->left_child);
            }else
                root = dummy;

            delete n;
        }
        else if(n->left_child != dummy && n->right_child != dummy){
            BSTNode* alternative = findMax(n->left_child);
            n->val = alternative->val;
            deleteNode(alternative);
        }
        else{
            //has one child
            BSTNode* onlyChild = (n->left_child != dummy) ? n->left_child : n->right_child;
            if(n->parent){
                relink(n->parent, onlyChild, n == n->parent->left_child);
            }
            else{
                root = onlyChild;
                root->parent = nullptr;
            }
            delete n;
        }
    }

    BSTNode* search(BSTNode* n, int val){
        if(n == dummy)
            return dummy;

        if(n->val == val)
            return n;

        if(val < n->val)
            return search(n->left_child, val);
        return search(n->right_child, val);
    }

    BSTNode* lowerBound(BSTNode* n, int val){
        BSTNode* res = nullptr;
        while(n){
            if(n->val >= val){
                res = n;
                n = n->left_child;
            }
            else
                n = n->right_child;
        }

        return res;
    }

    BSTNode* upperBound(BSTNode* n, int val){
        BSTNode* res = nullptr;
        while(n){
            if(n->val > val){
                res = n;
                n = n->left_child;
            }
            else
                n = n->right_child;
        }

        return res;
    }

public:
    AVLTree(){
        dummy = new BSTNode(0);
        dummy->left_child = dummy->right_child = dummy;
        root = dummy;
    }

    ~AVLTree(){
        delete root;
        delete dummy;
    }

    void insert(int val){
        if(root == dummy){
            root = new BSTNode(val, nullptr, dummy, dummy);
            return;
        }

        BSTNode* parent = nullptr;
        BSTNode* curr = root;
        while(curr != dummy){
            parent = curr;
            if(val < curr->val){
                curr = curr->left_child;
            }
            else if(val > curr->val){
                curr = curr->right_child;
            }
            else
                return;
        }

        BSTNode* newNode = new BSTNode(val, parent, dummy, dummy);
        if(val < parent->val)
            parent->left_child = newNode;
        else
            parent->right_child = newNode;

        rebalance(newNode);
    }


    void deleteVal(int val){
        BSTNode* valNode = search(root, val);
        if(valNode != dummy){
            deleteNode(valNode);
            rebalance(valNode->parent);
        }
    }

    int upperBound(int val){
        BSTNode* res = upperBound(root, val);
        return res != dummy ? res->val : -1;
    }

    int lowerBound(int val){
        BSTNode* res = lowerBound(root, val);
        return res != dummy ? res->val : -1;
    }

};

int main(){
    int n, q, newVal; cin >> n >> q;

    AVLTree* myAVL = new AVLTree();
    for(int i=0; i<n; i++){
        cin >> newVal;
        myAVL->insert(newVal);
    }

    for(int i=0; i<q; i++){
        char op; cin >> op;
        int val; cin >> val;
        if(op == 'U')
            cout << myAVL->upperBound(val);
        else if(op == 'L')
            cout << myAVL->lowerBound(val);
    }


    return 0;
}