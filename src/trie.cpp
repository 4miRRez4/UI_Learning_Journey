#include "../include/trie.h"

Trie::TrieNode::TrieNode(){
    isEndOfWord = false;
    word = "";
    for(int i=0; i<26; i++)
        children[i] = nullptr;
}

Trie::TrieNode::~TrieNode(){
    for (TrieNode* child : children) {
        delete child;
    }
}

Trie::Trie(){
    root = new TrieNode();
}

Trie::~Trie(){
    delete root;
}

void Trie::insert(const string& word){
    TrieNode* iterNode = root;
    for(char c : word){
        int index = tolower(c) - 'a';
        if(!iterNode->children[index]){
            iterNode->children[index] = new TrieNode();
        }

        iterNode = iterNode->children[index];
    }
    iterNode->isEndOfWord = true;
    iterNode->word = word;
}