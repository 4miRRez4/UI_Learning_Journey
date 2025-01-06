#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;
class Trie{
private:
    struct TrieNode{
        bool isEndOfWord;
        string word;
        TrieNode* children[26];

        TrieNode();
        ~TrieNode();
    };

    TrieNode* root;

public:
    Trie();
    ~Trie();

    void insert(const string& word);

};

#endif