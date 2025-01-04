#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "invertedIndex.h"

class QueryProcessor{
private:
    InvertedIndex* inverted;

    bool checkErrors(string query, set<string>& mustBeWords,
                    set<string>& mustNotBeWords,
                    set<string>& atLeastOneOfWords);

    void lowerQuery(string& query);

    void parseQuery(string query,
                    set<string>& mustBeWords,
                    set<string>& mustNotBeWords,
                    set<string>& atLeastOneOfWords);

public:
    QueryProcessor(InvertedIndex* ii);

    set<string> processQuery(string& query);

};

#endif