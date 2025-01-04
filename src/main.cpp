#include <iostream>
#include "../include/preprocessor.h"
#include "../include/map.h"
#include "../include/invertedIndex.h"
#include "../include/queryProcessor.h"

void displayResults(const std::set<string>& results) {
    if (results.empty()) {
        std::cout << "No matching documents found.\n";
    } else {
        std::cout << "Matching Documents: ";
        cout << results.size() << endl;
        for (string docID : results) {
            std::cout << docID << endl;
        }
        std::cout << std::endl;
    }
}

int main(){
    Preprocessor* preprocessor = new Preprocessor();

    string directory = "EnglishData";
    cout << "Preprocessing documents in directory: " << directory << std::endl;
    preprocessor->readFiles(directory);

    const vector<pair<string, vector<string>>>& processedDocs = preprocessor->getProcessedDocs();

    InvertedIndex* invertedMap = new InvertedIndex();
    invertedMap->buildInvertedMap(processedDocs);


    QueryProcessor* qp = new QueryProcessor(invertedMap);

    std::cout << "Enter a query (or 'exit' to quit): ";
    std::string query;
    while (std::getline(std::cin, query) && query != "exit") {
        std::set<string> results = qp->processQuery(query);
        displayResults(results);
        std::cout << "Enter a query (or 'exit' to quit): ";
        
    }

    delete preprocessor;
    delete invertedMap;
    
    return 0;
}