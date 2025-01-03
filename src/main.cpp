#include <iostream>
#include "../include/preprocessor.h"
#include "../include/map.h"

int main(){
    // Preprocessor preprocessor;

    // string directory = "EnglishData";
    // cout << "Preprocessing documents in directory: " << directory << std::endl;
    // preprocessor.readFiles(directory);

    // const auto& processedDocs = preprocessor.getProcessedDocs();


    // for (const auto& [docID, tokens] : processedDocs) {
    //     std::cout << "\nDocument ID: " << docID << std::endl;
    //     std::cout << "Content:\n";
    //     for (const auto& token : tokens) {
    //         std::cout << token << " ";
    //     }
    //     std::cout << "\n-----------------------------" << std::endl;
    // }

    // if (processedDocs.empty()) {
    //     std::cout << "No documents were processed. Ensure the 'data' directory contains valid files." << std::endl;
    // }

    Map* map = new Map();

    // Insert some key-value pairs
    map->insert("hello", {"doc1", "doc2"});
    map->insert("world", {"doc5", "doc6"});

    // Search for a key
    std::string key = "hello";
    auto result = map->search(key);
    if (!result.empty()) {
        std::cout << "Key: " << key << " -> Values: ";
        for (string val : result) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Key '" << key << "' not found." << std::endl;
    }

    // Remove a key
    if (map->remove("hello")) {
        std::cout << "Key 'hello' removed successfully." << std::endl;
    } else {
        std::cout << "Key 'hello' not found." << std::endl;
    }

    return 0;
}