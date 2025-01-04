#include <iostream>
#include "../include/preprocessor.h"
#include "../include/map.h"
#include "../include/invertedIndex.h"

int main(){
    Preprocessor* preprocessor = new Preprocessor();

    string directory = "EnglishData";
    cout << "Preprocessing documents in directory: " << directory << std::endl;
    preprocessor->readFiles(directory);

    const vector<pair<string, vector<string>>>& processedDocs = preprocessor->getProcessedDocs();

    InvertedIndex* invertedMap = new InvertedIndex();
    invertedMap->buildInvertedMap(processedDocs);

    std::cout << "Testing Inverted Index..." << std::endl;
    std::string query;
    std::cout << "Enter a word to search (or 'exit' to quit): ";
    while (std::cin >> query && query != "exit") {
        std::set<string>& result = invertedMap->search(query);

        if (!result.empty()) {
            std::cout << "Documents containing '" << query << "': ";
            for (string docID : result) {
                std::cout << docID << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No documents contain the word '" << query << "'." << std::endl;
        }

        std::cout << "Enter a word to search (or 'exit' to quit): ";
    }

    delete preprocessor;
    delete invertedMap;
    
    return 0;
}