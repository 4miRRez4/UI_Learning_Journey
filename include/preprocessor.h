#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>
#include <vector>
using namespace std;

class Preprocessor{
private:
    vector<pair<string, vector<string>>> processedDocs;

    string cleanText(const string& text);
    vector<string> tokenize(const string& cleanedText);
public:
    void readFiles(const string directory);

    vector<pair<string, vector<string>>>& getProcessedDocs();
};

#endif