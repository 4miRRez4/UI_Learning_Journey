#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "map.h"
#include <vector>
using namespace std;

class InvertedIndex{
private:
    Map* invertedMap; 
    // word -> doc1, doc2, ...
    //AdvancedMode: word -> doc1 index1 index2, doc2 index, ...

public:
    InvertedIndex();
    
    void buildInvertedMap(const vector<pair<string, vector<string>>>& processedDocs);
    set<string>& search(const string& word) const;

    void buildPhraseIndex(const vector<pair<string, vector<string>>>& processedDocs);
    set<string> searchPhrase(const string& phrase) const;
    
};

#endif 