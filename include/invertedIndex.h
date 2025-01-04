#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "map.h"
#include <vector>
using namespace std;

class InvertedIndex{
private:
    Map* invertedMap; // word -> doc1, doc2, ...

public:
    InvertedIndex();
    
    void buildInvertedMap(const vector<pair<string, vector<string>>>& processedDocs);
    set<string>& search(const string& word) const;
};

#endif 