#include <iostream>
#include "../include/preprocessor.h"
#include "../include/map.h"
#include "../include/invertedIndex.h"
#include "../include/queryProcessor.h"

void displayResults(const std::set<string>& results) {
        cout << results.size() << endl;
        for (string docID : results) {
            cout << docID << endl;
        }
        cout << endl;
}


void lowerQuery(string& query){
    for(char &c : query)
        c = tolower(c);
}

int main(){
    bool AdvancedModeFuzzy = false;
    bool AdvancedModePhrase = false;
    
    cin >> AdvancedModeFuzzy;
    cin >> AdvancedModePhrase;

    Preprocessor* preprocessor = new Preprocessor();

    // string directory; cin >> directory;
    preprocessor->readFiles("Data/EnglishData");

    const vector<pair<string, vector<string>>>& processedDocs = preprocessor->getProcessedDocs();

    InvertedIndex* invertedMap = new InvertedIndex();
    if(AdvancedModePhrase){
        invertedMap->buildPhraseIndex(processedDocs);

        string phrase; 
        cin.ignore();
        getline(cin, phrase);
        lowerQuery(phrase);
        set<string> results = invertedMap->searchPhrase(phrase);
        displayResults(results);
    }
    else{

        invertedMap->buildInvertedMap(processedDocs);

        Trie* trie = new Trie();
        trie->buildTrie(processedDocs);

        QueryProcessor* qp = new QueryProcessor(AdvancedModeFuzzy, invertedMap, trie);

        string query;
        int n; cin >> n;
        cin.ignore();
        for(int i=0; i<n; i++){
            getline(cin, query);
            lowerQuery(query);
            set<string> results = qp->processQuery(query);
            displayResults(results);        
        }
    }
    

    delete preprocessor;
    delete invertedMap;
    
    return 0;
}