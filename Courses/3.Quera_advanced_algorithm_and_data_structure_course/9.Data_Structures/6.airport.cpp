#include <iostream>
using namespace std;


template<typename T>
class BST{
public:
    struct Node{
        T data;
        Node<T>* right;
        Node<T>* left;

        Node(T d): data(d), right(nullptr), left(nullptr){}
    };

    Node<T>* root;

    BST(): root(nullptr){}

    void insert(Node* root, T val){
        if(root == nullptr){
            Node<T>* newNode = new Node(val);
            return newNode;
        }
        if(val < root->data)
            root->left = insert(root->left, val);
        else if(val > root->data)
            root->right = insert(root->right, val);

        return root;
    }

    
};


int main(){


    return 0;
}