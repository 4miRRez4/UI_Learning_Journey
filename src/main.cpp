#include <iostream>
#include "../include/preprocessor.h"

int main(){
    Preprocessor preprocessor;

    string directory = "EnglishData";

    cout << "Preprocessing documents in directory: " << directory << std::endl;
    preprocessor.readFiles(directory);

    const auto& processedDocs = preprocessor.getProcessedDocs();


    for (const auto& [docID, tokens] : processedDocs) {
        std::cout << "\nDocument ID: " << docID << std::endl;
        std::cout << "Content:\n";
        for (const auto& token : tokens) {
            std::cout << token << " ";
        }
        std::cout << "\n-----------------------------" << std::endl;
    }

    if (processedDocs.empty()) {
        std::cout << "No documents were processed. Ensure the 'data' directory contains valid files." << std::endl;
    }
}