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

        //just handle alphabetic
        if(index < 0 || index >= 26)
            continue;
            
        if(!iterNode->children[index]){
            iterNode->children[index] = new TrieNode();
        }

        iterNode = iterNode->children[index];
    }
    iterNode->isEndOfWord = true;
    iterNode->word = word;
}

void Trie::buildTrie(const vector<pair<string, vector<string>>>& processedDocs){
    for(const auto& [docID, tokens] : processedDocs)
        for(const auto& word : tokens)
            insert(word);
}


bool Trie::isNextCharValid(TrieNode* node, int nextCharInd){
    return !(nextCharInd < 0 || nextCharInd >=26 || !node->children[nextCharInd]);
}

vector<string> Trie::fuzzySearch(const string& word, int maxDis){
    vector<string> similars;

    TrieNode* iterNode = root;

    //Traverse trie to depth "word.size() - maxDis - 1"
    int currDepth;
    for(currDepth=0; currDepth < word.size() - maxDis - 1; currDepth++){
        int nextCharInd = tolower(word[currDepth]) - 'a';

        //check if nextCharInd is valid
        if(!isNextCharValid(iterNode, nextCharInd))
            return similars;

        iterNode = iterNode->children[nextCharInd];
    }

    //do dfs like explore from `currDepth` to `word.size() + maxDis - 1`
    for(currDepth; currDepth < word.size() + maxDis - 1; currDepth++){
        for(int i=0; i<26; i++){
            if(iterNode->children[i] && iterNode->children[i]->isEndOfWord)
                similars.push_back(iterNode->children[i]->word);
        }

        //move to next char in word
        int nextCharInd = tolower(word[currDepth]) - 'a';
        if (!isNextCharValid(iterNode, nextCharInd)) {
            break;
        }

        iterNode = iterNode->children[nextCharInd];
    }

    return similars;
}