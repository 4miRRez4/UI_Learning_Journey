#include "../include/preprocessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

string Preprocessor::cleanText(const string& text){
    string cleaned="";

    for(char c : text){
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ') {
            if (c >= 'A' && c <= 'Z') {
                cleaned += c + ('a' - 'A');
            } else 
                cleaned += c;
        }
        else if(c == '\n')
            cleaned += " ";
    }

    return cleaned;
}

vector<string> Preprocessor::tokenize(const string& cleanedText){
    vector<string> tokens;
    stringstream ss(cleanedText);
    string word;

    while(ss >> word)
        tokens.push_back(word);

    return tokens;
}

void Preprocessor::readFiles(const std::string dir){
    for(const auto& file : filesystem::directory_iterator(dir)){
        if(file.is_regular_file()){
            ifstream inFile(file.path());
            if(!inFile.is_open()){
                cerr << "Error in opening file: " << file.path() << endl;
                continue;
            }

            string docID = file.path().stem().string();

            string text="", line="";
            while(getline(inFile, line))
                text += line + " ";


            string cleanedText = cleanText(text);
            vector<string> tokens = tokenize(cleanedText);

            processedDocs.emplace_back(docID, tokens);

            inFile.close();
        }
    }
}

vector<pair<string, vector<string>>>& Preprocessor::getProcessedDocs(){
    return processedDocs;
}