#include "../include/invertedIndex.h"
#include <algorithm>


InvertedIndex::InvertedIndex(){
    invertedMap = new Map();
}

void InvertedIndex::buildInvertedMap(const vector<pair<string, vector<string>>>& processedDocs){
    for(const auto& [docID, tokens] : processedDocs){
        for(const auto& word : tokens){
            vector<string>& docIDs = invertedMap->search(word);

            //adding doc if it's not already added
            if(docIDs.empty())
                invertedMap->insert(word, {docID});
            else if(find(docIDs.begin(), docIDs.end(), docID) == docIDs.end())
                docIDs.push_back(docID);
        }
    }
}

vector<string>& InvertedIndex::search(const string& word) const{
    return invertedMap->search(word);
}