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

    Node<T>* insert(Node<T>* root, T val){
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

    Node<T>* clear(Node<T>* curr){
        if(curr == nullptr)
            return nullptr; 
        clear(curr->right);
        clear(curr->left);
        delete curr;
        return nullptr;
    }

    Node<T>* find_min(Node<T>* n){
        Node<T>* curr = n;
        while(curr && curr->left)
            curr = curr->left;
        return curr;
    }

    Node<T>* find_max(Node<T>* n){
        Node<T>* curr = n;
        while (curr && curr->right)
            curr = curr->right;
        return curr;   
    }

    Node<T>* remove(Node<T>* root, T val){
        if(val < root->data)
            root->left = remove(root->left, val);   
        else if(val > root->data)
            root->right = remove(root->right, val);
        else{
            Node<T>* tmp;
            if(root->right == nullptr){
                tmp = root->left;
                delete root;
                return tmp;
            }
            else if(root->left == nullptr){
                tmp = root->right;
                delete root;
                return tmp;
            }

            tmp = find_min(root->right);
            root->data = tmp->data;
            root->right = remove(root->right, tmp->data);
        }
        return root;
    }

    Node<T>* find(Node<T>* n, T val){
        if(n == nullptr || n->data == val)
            return n;
        if(val < n->data)
            return find(n->left, val);
        //val > n->data
        return find(n->right, val);
    }

    ~BST(){ root = clear(root); }
};
//TODO: test and lowerBound, upperBound then 66666