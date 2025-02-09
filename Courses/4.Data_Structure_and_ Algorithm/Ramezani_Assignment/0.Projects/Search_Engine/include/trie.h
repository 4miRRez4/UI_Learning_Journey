#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
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


    bool isNextCharValid(TrieNode* node, int nextCharInd);
public:
    Trie();
    ~Trie();

    void insert(const string& word);

    void buildTrie(const vector<pair<string, vector<string>>>& processedDocs);

    vector<string> fuzzySearch(const string& word, int maxDis);
};

#endif