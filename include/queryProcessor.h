#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "invertedIndex.h"
#include "trie.h"

const int MAX_EDIT_DIS = 1;

class QueryProcessor{
private:
    bool AdvancedMode;

    InvertedIndex* inverted;
    Trie* trie;

    bool checkErrors(string query, set<string>& mustBeWords,
                    set<string>& mustNotBeWords,
                    set<string>& atLeastOneOfWords);

    void lowerQuery(string& query);

    void parseQuery(string query,
                    set<string>& mustBeWords,
                    set<string>& mustNotBeWords,
                    set<string>& atLeastOneOfWords);

    set<string> findSimilarWords(const string& word);

    void addSimilarWords(const string& orgWord, set<string>& wordSet);

public:
    QueryProcessor(InvertedIndex* ii, Trie* t);

    void goAdvanced();

    set<string> processQuery(string& query);

};

#endif