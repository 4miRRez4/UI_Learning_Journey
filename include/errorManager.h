#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <set>
#include <string>
#include <vector>
using namespace std;

class ErrorManager{
private:
    bool isTokenValid(const string& token);

public:
    bool hasInputError(const string& query);

    bool hasLogicalError(set<string>& mustBeWords,
                            set<string>& mustNotBeWords,
                            set<string>& atLeastOneOfWords);
};

#endif