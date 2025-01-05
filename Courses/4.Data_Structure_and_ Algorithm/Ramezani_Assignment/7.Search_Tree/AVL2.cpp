#include <iostream>
using namespace std;

class AVLTree {
private:
    struct BSTNode {
        int val;
        int height;
        BSTNode* left_child;
        BSTNode* right_child;

        BSTNode(int v, BSTNode* l = nullptr, BSTNode* r = nullptr, int h = 0)
            : val(v), left_child(l), right_child(r), height(h) {}
    };

    BSTNode* root;
    BSTNode* dummy;

    int height(BSTNode* n) { return n != dummy ? n->height : 0; }

    int getBalance(BSTNode* n) { return n != dummy ? height(n->left_child) - height(n->right_child) : 0; }

    void recomputeHeight(BSTNode* n) {
        if (n != dummy)
            n->height = 1 + max(height(n->left_child), height(n->right_child));
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

    BSTNode* rightRotation(BSTNode* y) {
        BSTNode* x = y->left_child;
        BSTNode* T2 = x->right_child;

        x->right_child = y;
        y->left_child = T2;

        recomputeHeight(y);
        recomputeHeight(x);

        return x;
    }

    BSTNode* leftRotation(BSTNode* y) {
        BSTNode* x = y->right_child;
        BSTNode* T2 = x->left_child;

        x->left_child = y;
        y->right_child = T2;

        recomputeHeight(y);
        recomputeHeight(x);

        return x;
    }

    BSTNode* findMax(BSTNode* n) {
        while (n->right_child != dummy)
            n = n->right_child;
        return n;
    }

    BSTNode* balance(BSTNode* n) {
        recomputeHeight(n);
        int balance = getBalance(n);

        if (balance > 1) {
            if (getBalance(n->left_child) < 0)
                n->left_child = leftRotation(n->left_child);
            return rightRotation(n);
        }

        if (balance < -1) {
            if (getBalance(n->right_child) > 0)
                n->right_child = rightRotation(n->right_child);
            return leftRotation(n);
        }

        return n;
    }

    BSTNode* insert(BSTNode* n, int val) {
        if (n == dummy)
            return new BSTNode(val, dummy, dummy);

        if (val < n->val)
            n->left_child = insert(n->left_child, val);
        else if (val > n->val)
            n->right_child = insert(n->right_child, val);
        else
            return n;

        return balance(n);
    }

    BSTNode* deleteNode(BSTNode* n, int val) {
        if (n == dummy)
            return dummy;

        if (val < n->val)
            n->left_child = deleteNode(n->left_child, val);
        else if (val > n->val)
            n->right_child = deleteNode(n->right_child, val);
        else {
            if (n->left_child == dummy || n->right_child == dummy) {
                BSTNode* temp = (n->left_child != dummy) ? n->left_child : n->right_child;
                delete n;
                return temp;
            }

            BSTNode* maxNode = findMax(n->left_child);
            n->val = maxNode->val;
            n->left_child = deleteNode(n->left_child, maxNode->val);
        }

        return balance(n);
    }

    void destroyTree(BSTNode* n) {
        if (n == dummy) return;
        destroyTree(n->left_child);
        destroyTree(n->right_child);
        delete n;
    }

public:
    AVLTree() {
        dummy = new BSTNode(0);
        dummy->left_child = dummy->right_child = dummy;
        root = dummy;
    }

    ~AVLTree() {
        destroyTree(root);
        delete dummy;
    }

    void insertVal(int val) { root = insert(root, val); }

    void deleteVal(int val) { root = deleteNode(root, val); }

    bool search(int val) { return search(root, val); }

    int lowerBound(int val) {
        BSTNode* res = nullptr;
        BSTNode* n = root;
        while (n != dummy) {
            if (n->val >= val) {
                res = n;
                n = n->left_child;
            } else {
                n = n->right_child;
            }
        }
        return res ? res->val : -1;
    }

    int upperBound(int val) {
        BSTNode* res = nullptr;
        BSTNode* n = root;
        while (n != dummy) {
            if (n->val > val) {
                res = n;
                n = n->left_child;
            } else {
                n = n->right_child;
            }
        }
        return res ? res->val : -1;
    }
};

int main() {
    AVLTree tree;

    int n, q, newVal;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> newVal;
        tree.insertVal(newVal);
    }

    for (int i = 0; i < q; ++i) {
        char op;
        int val;
        cin >> op >> val;
        if (op == 'U')
            cout << tree.upperBound(val) << endl;
        else if (op == 'L')
            cout << tree.lowerBound(val) << endl;
    }

    return 0;
}
