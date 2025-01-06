#include <sstream>
#include <iostream>
#include "../include/queryProcessor.h"
#include "../include/setOperations.h"
#include "../include/errorManager.h"

QueryProcessor::QueryProcessor(InvertedIndex* ii, Trie* t): AdvancedMode(false), inverted(ii), trie(t){};

void QueryProcessor::goAdvanced(){
    AdvancedMode = true;
}

void QueryProcessor::parseQuery(string query,
                                set<string>& mustBeWords,
                                set<string>& mustNotBeWords,
                                set<string>& atLeastOneOfWords)
{
    stringstream ss(query);
    string token;

    while(ss >> token){
        if(token[0] == '-'){
            mustNotBeWords.insert(token.substr(1));
        }
        else if(token[0] == '+'){
            atLeastOneOfWords.insert(token.substr(1));
        }
        else{
            mustBeWords.insert(token);
        }
    }

}

bool QueryProcessor::checkErrors(string query, set<string>& mustBeWords,
                                set<string>& mustNotBeWords, 
                                set<string>& atLeastOneOfWords){

    ErrorManager* EM = new ErrorManager();

    if(EM->hasInputError(query)){
        cout << "Invalid Input" << endl;
        return true;
    }

    if(EM->hasLogicalError(mustBeWords, mustNotBeWords, atLeastOneOfWords)){
        cout << "Logical Error" << endl;
        return true;
    }

    return false;
}

void QueryProcessor::lowerQuery(string& query){
    for(char &c : query)
        c = tolower(c);
}

set<string> QueryProcessor::findSimilarWords(const string& word){
    vector<string> fuzzyOnTrie = trie->fuzzySearch(word, MAX_EDIT_DIS);
    
    set<string> similars;
    similars.insert(fuzzyOnTrie.begin(), fuzzyOnTrie.end());
    return similars;
}

void QueryProcessor::addSimilarWords(const string& orgWord, set<string>& wordSet){

    vector<string> fuzzyOnTrie = trie->fuzzySearch(orgWord, MAX_EDIT_DIS);

    wordSet.insert(fuzzyOnTrie.begin(), fuzzyOnTrie.end());
}

set<string> QueryProcessor::processQuery(string& query){
    lowerQuery(query);


    set<string> mustBeWords;
    set<string> mustNotBeWords;
    set<string> atLeastOneOfWords;

    //split words in these 3 groups
    parseQuery(query, mustBeWords, mustNotBeWords, atLeastOneOfWords);

    if(checkErrors(query, mustBeWords, mustNotBeWords, atLeastOneOfWords))
        return {};

    if(AdvancedMode){
        set<string> copy = mustBeWords;
        for(string word : copy){
            set<string>& docIDs = inverted->search(word);

            //just do fuzzy if the mustBeWord doesn't exist
            if(docIDs.empty()){
                addSimilarWords(word, mustBeWords);

                //erase the word cause it's not in any doc
                mustBeWords.erase(word);
            }
        }

        copy = atLeastOneOfWords;
        for(string word : copy)
            addSimilarWords(word, atLeastOneOfWords);

        //no fuzzy logic for mustNotBeWords
    }


    set<string> answerDocs;

    //process words which at least one of them should be in the answer doc.(logical OR)
    for(const string& word : atLeastOneOfWords){
        set<string>& docIDs = inverted->search(word);

        //union
        answerDocs = setOperations::unionSets(answerDocs, docIDs);
    }

    //process words that must be in the anwer doc.(logical And, intersection);
    for(const string& word : mustBeWords){
        set<string>& docIDs = inverted->search(word);

        //intersection
        if(answerDocs.empty()){ //intersection with empty set is always empty.(first word)
            answerDocs = docIDs;
        }else{
            answerDocs = setOperations::intersectionSets(answerDocs, docIDs);
        }
    }

    //process words that must not be in the answer doc.(logical NOT)
    for(const string& word : mustNotBeWords){
        set<string>& docIDs = inverted->search(word);

        //difference
        answerDocs = setOperations::differenceSets(answerDocs, docIDs);
    }

    return answerDocs;
}