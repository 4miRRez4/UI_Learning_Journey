#include "../include/invertedIndex.h"
#include <algorithm>


InvertedIndex::InvertedIndex(){
    invertedMap = new Map();
}

void InvertedIndex::buildInvertedMap(const vector<pair<string, vector<string>>>& processedDocs){
    for(const auto& [docID, tokens] : processedDocs){
        for(const auto& word : tokens){
            set<string>& docIDs = invertedMap->search(word);

            if(docIDs.empty())
                invertedMap->insert(word, {docID}); //insert new entry for not founded word
            else
                docIDs.insert(docID); //add new doc to the word

        }
    }
}

set<string>& InvertedIndex::search(const string& word) const{
    return invertedMap->search(word);
}