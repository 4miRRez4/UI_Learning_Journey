#include "../include/errorManager.h"
#include "../include/setOperations.h"
#include <sstream>

bool ErrorManager::isTokenValid(const string& token){
    for(int i=0; i<token.length(); i++){
        char c = token[i];

        if(i == 0 && (c == '+' || c == '-')){
            continue;
        }
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            continue;
        }
        return false;
    }

    return true;
}

bool ErrorManager::hasInputError(const string& query){
    stringstream ss(query);
    string token;
    while (ss >> token) {
        if(!isTokenValid(token))
            return true;
    }

    return false;
}

bool ErrorManager::hasLogicalError(set<string>& mustBeWords,
                                    set<string>& mustNotBeWords,
                                    set<string>& atLeastOneOfWords){
    //check intersection of mustNotBeWords with mustBeWords
    set<string> interWithMB = setOperations::intersectionSets(mustNotBeWords, mustBeWords);
    if(!interWithMB.empty()){
        return true;
    }

    // //check intersection of mustNotBeWords with atLeastOneOfWords
    // set<string> interWithLO = setOperations::intersectionSets(mustNotBeWords, atLeastOneOfWords);
    // if(!interWithLO.empty()){
    //     return true;
    // }

    return false;
}