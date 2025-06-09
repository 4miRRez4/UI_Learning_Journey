#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class BPlusTree{
private:

    struct BP_Node{
        bool isLeaf;
        vector<T> keys;
        vector<BP_Node*> children;
        BP_Node* next_leaf;
        BP_Node* parent;

        BP_Node(bool leaf = false) : isLeaf(leaf), next_leaf(nullptr), parent(nullptr) {}
    };

    const int min_degree; // minimum number of keys
    BP_Node* root;

    void splitChild(BP_Node* parent, int idx, BP_Node* child);

    void insertInNonFull(BP_Node* node, T new_key);

    void removeFromNode(BP_Node* node, T key);

    void borrowFromPrevSib(BP_Node* node, int idx);

    void borrowFromNextSib(BP_Node* node, int idx);

    void merge(BP_Node* node, int idx);

    void printTree(BP_Node* node, int lvl);

    int countKeys(BP_Node* node) const;

public:
    BPlusTree(int m=2) : root(nullptr), min_degree(m) {}

    void insert(T key);
    void remove(T key);
    bool search(T key);
    int countKeys() const;

    vector<T> rangeQuery(T lower, T upper) const;
    void printTree();
};

template <typename T>
bool BPlusTree<T>::search(T key){
    BP_Node* curr = root;
    while (curr != nullptr)
    {
        int idx = 0;
        while(idx < curr->keys.size() && key > curr->keys[idx]){
            idx++;
        }

        if(idx < curr->keys.size() && key == curr->keys[idx]){
            return true; // found
        }
        if(curr->isLeaf){
            return false; // no where to search
        }

        curr = curr->children[idx];
    }

    return false;   
}

template<typename T>
int BPlusTree<T>::countKeys(BP_Node* node) const {
    if (!node) return 0;

    int count = node->keys.size();
    if (!node->isLeaf) {
        for (BP_Node* child : node->children) {
                count += countKeys(child);
        }
    }
    return count;
}

template<typename T>
int BPlusTree<T>::countKeys() const {
    return countKeys(root);
}

template <typename T>
void BPlusTree<T>::splitChild(BP_Node* parent, int idx, BP_Node* child){
    BP_Node* newChild = new BP_Node(child->isLeaf);

    parent->children.insert(parent->children.begin() + idx + 1, newChild);
    parent->keys.insert(parent->keys.begin() + idx, child->keys[min_degree - 1]);

    newChild->keys.assign(child->keys.begin() + min_degree, child->keys.end());
    child->keys.resize(min_degree - 1);

    if(!child->isLeaf){
        newChild->children.assign(child->children.begin() + min_degree, child->children.end());

        child->children.resize(min_degree);
    }

    if(child->isLeaf){
        newChild->next_leaf = child->next_leaf;
        child->next_leaf = newChild;
    }
}

template <typename T>
void BPlusTree<T>::insertInNonFull(BP_Node* node, T key){
    if(node->isLeaf){
        node->keys.insert(upper_bound(node->keys.begin(), node->keys.end(), key), key);
    }
    else{
        int i = node->keys.size() -1;
        while(i >= 0 && key < node->keys[i]){
            i--;
        }
        i++;

        if(node->children[i]->keys.size() == 2*min_degree - 1){
            splitChild(node, i, node->children[i]);
            if(key > node->keys[i]){
                i++;
            }
        }
        insertInNonFull(node->children[i], key);
    }
}

template <typename T>
void BPlusTree<T>::insert(T key){
    if(root == nullptr){ //empty tree
        root = new BP_Node(true);
        root->keys.push_back(key);
    }
    else{
        if(root->keys.size() == 2*min_degree - 1){
            BP_Node* newRoot = new BP_Node();
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertInNonFull(root, key);
    }
}

template <typename T>
void BPlusTree<T>::borrowFromPrevSib(BP_Node* node, int idx)
{
    BP_Node* child = node->children[idx];
    BP_Node* sibling = node->children[idx - 1];

    child->keys.insert(child->keys.begin(), node->keys[idx - 1]);
    node->keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();

    if (!child->isLeaf) {
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
    }
}

template <typename T>
void BPlusTree<T>::borrowFromNextSib(BP_Node* node, int idx)
{
    BP_Node* child = node->children[idx];
    BP_Node* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);
    node->keys[idx] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());

    if (!child->isLeaf) {
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }
}

template <typename T>
void BPlusTree<T>::merge(BP_Node* node, int idx)
{
    BP_Node* child = node->children[idx];
    BP_Node* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
    if (!child->isLeaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }

    node->keys.erase(node->keys.begin() + idx);
    node->children.erase(node->children.begin() + idx + 1);

    delete sibling;
}

template <typename T>
void BPlusTree<T>::removeFromNode(BP_Node* node, T key){
    if(node->isLeaf){
        auto it = find(node->keys.begin(), node->keys.end(), key);
        if(it != node->keys.end()){
            node->keys.erase(it);
        }
    }
    else{
        int idx = lower_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();

        if(idx < node->keys.size() && node->keys[idx] == key){
            if(node->children[idx]->keys.size() >= min_degree){
                BP_Node* predNode = node->children[idx];
                while (!predNode->isLeaf) {
                    predNode = predNode->children.back();
                }
                T pred = predNode->keys.back();
                node->keys[idx] = pred;
                removeFromNode(node->children[idx], pred);
            }
            else if (node->children[idx + 1]->keys.size() >= min_degree) {
                BP_Node* succNode = node->children[idx + 1];
                while (!succNode->isLeaf) {
                    succNode = succNode->children.front();
                }
                T succ = succNode->keys.front();
                node->keys[idx] = succ;
                removeFromNode(node->children[idx + 1], succ);
            }
            else{
                merge(node, idx);
                removeFromNode(node->children[idx], key);
            }
        }
        else {
            if (node->children[idx]->keys.size() < min_degree) {
                if (idx > 0 && node->children[idx - 1]->keys.size() >= min_degree) {
                    borrowFromPrevSib(node, idx);
                }
                else if (idx < node->children.size() - 1 && node->children[idx + 1]->keys.size() >= min_degree) {
                    borrowFromNextSib(node, idx);
                }
                else {
                    if (idx < node->children.size() - 1) {
                        merge(node, idx);
                    }
                    else {
                        merge(node, idx - 1);
                    }
                }
            }
            removeFromNode(node->children[idx], key);
        }
    }
}

template <typename T>
void BPlusTree<T>::printTree(BP_Node* node, int level)
{
    if (node != nullptr) {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        for (const T& key : node->keys) {
            cout << key << " ";
        }
        cout << endl;
        for (BP_Node* child : node->children) {
            printTree(child, level + 1);
        }
    }
}

template <typename T> void BPlusTree<T>::printTree()
{
    printTree(root, 0);
}

template <typename T>
vector<T> BPlusTree<T>::rangeQuery(T lower, T upper) const
{
    vector<T> result;
    BP_Node* current = root;
    while (!current->isLeaf) {
        int i = 0;
        while (i < current->keys.size()
               && lower > current->keys[i]) {
            i++;
        }
        current = current->children[i];
    }
    while (current != nullptr) {
        for (const T& key : current->keys) {
            if (key >= lower && key <= upper) {
                result.push_back(key);
            }
            if (key > upper) {
                return result;
            }
        }
        current = current->next_leaf;
    }
    return result;
}

template <typename T> void BPlusTree<T>::remove(T key)
{
    if (root == nullptr) {
        return;
    }
    removeFromNode(root, key);
    if (root->keys.empty() && !root->isLeaf) {
        BP_Node* tmp = root;
        root = root->children[0];
        delete tmp;
    }
}

#endif