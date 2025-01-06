#include "../include/preprocessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>

string Preprocessor::cleanText(const string& text){
    string cleaned="";

    for(char c : text){
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ') {
            if (c >= 'A' && c <= 'Z') {
                cleaned += c + ('a' - 'A');
            } else 
                cleaned += c;
        }
        else
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

string Preprocessor::parseTxtFile(const string filePath){
    ifstream infile(filePath);
    if(!infile.is_open()){
        throw runtime_error("Error opening text file: " + filePath);
    }

    string text = "", line = "";
    while(getline(infile, line)){
        text += line + " ";
    }

    infile.close();
    return text;
}


string Preprocessor::parseCsvFile(const string filePath){
    ifstream infile(filePath);
    if (!infile.is_open()) {
        throw runtime_error("Error opening CSV file: " + filePath);
    }

    string text ="", line = "";
    while(getline(infile, line)){
        stringstream ss(line);
        string part;
        while(getline(ss, part, ',')){
            text += part + " ";
        }
    }

    infile.close();
    return text;
}

string Preprocessor::parseJsonFile(const string filePath){
    ifstream infile(filePath);
    if (!infile.is_open()) {
        throw runtime_error("Error opening JSON file: " + filePath);
    }

    nlohmann::json jsonText;
    infile >> jsonText;
    infile.close();

    string text = "";
    for(const auto& [key, value] : jsonText.items()){
        text += key + " ";
        if(value.is_string()){
            text += value.get<string>() + " ";
        }
        else if (value.is_array() || value.is_object()) {
            text += value.dump() + " ";
        }
    }

    return text;
}


void Preprocessor::readFiles(const std::string dir){
    for(const auto& file : filesystem::directory_iterator(dir)){
        if(file.is_regular_file()){
            string fileType = file.path().extension().string(); 
            string docID = file.path().stem().string();


            string text="";

            if(fileType == ".txt"){
                text = parseTxtFile(file.path().string());
            }
            else if(fileType == ".csv"){
                text = parseCsvFile(file.path().string());
            }
            else if(fileType == ".json"){
                text = parseJsonFile(file.path().string());
            }


            string cleanedText = cleanText(text);
            vector<string> tokens = tokenize(cleanedText);

            processedDocs.emplace_back(docID, tokens);

        }
    }
}

vector<pair<string, vector<string>>>& Preprocessor::getProcessedDocs(){
    return processedDocs;
}