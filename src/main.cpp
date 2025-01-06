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

int main(){
    Preprocessor* preprocessor = new Preprocessor();

    // string directory; cin >> directory;
    preprocessor->readFiles("EnglishData");

    const vector<pair<string, vector<string>>>& processedDocs = preprocessor->getProcessedDocs();

    InvertedIndex* invertedMap = new InvertedIndex();
    invertedMap->buildInvertedMap(processedDocs);


    QueryProcessor* qp = new QueryProcessor(invertedMap);

    string query;
    // int n; cin >> n;
    // cin.ignore();
    // for(int i=0; i<n; i++){
        getline(cin, query);
        set<string> results = qp->processQuery(query);
        displayResults(results);        
    // }
    

    delete preprocessor;
    delete invertedMap;
    
    return 0;
}