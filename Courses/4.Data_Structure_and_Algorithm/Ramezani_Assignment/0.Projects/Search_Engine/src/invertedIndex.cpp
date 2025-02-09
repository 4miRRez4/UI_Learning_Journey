#include "../include/invertedIndex.h"
#include <algorithm>
#include <sstream>


InvertedIndex::InvertedIndex(){
    invertedMap = new Map();
}

void InvertedIndex::buildInvertedMap(const vector<pair<string, vector<string>>>& processedDocs){
    for(const auto& [docID, tokens] : processedDocs){
        for(const auto& word : tokens){
            set<string>& docIDs = invertedMap->search(word);

            if(docIDs.empty())
                invertedMap->insert(word, {docID}); //insert new entry for not founded word
            else
                docIDs.insert(docID); //add new doc to the word

        }
    }
}

void InvertedIndex::buildPhraseIndex(const vector<pair<string, vector<string>>>& processedDocs){
    for(const auto& [docID, tokens] : processedDocs){
        for(int pos=0; pos < tokens.size(); pos++){
            const string& word = tokens[pos];

            set<string>& wordPrevValues = invertedMap->search(word);

            if(wordPrevValues.empty()){
                //create entry for word
                string entry = docID + " " + to_string(pos);
                invertedMap->insert(word, {entry});
            }
            else{
                //find entry for this docID or create one
                bool docFound = false;
                for(const string& docEntry : wordPrevValues){
                    int firstSpacePos = docEntry.find(' ');
                    string currDocID = docEntry.substr(0, firstSpacePos);

                    if(currDocID == docID){
                        //update existing document entry
                        string newDocEntry = docEntry + " " + to_string(pos);
                        
                        wordPrevValues.erase(docEntry);
                        wordPrevValues.insert(newDocEntry);

                        docFound = true;
                        break;
                    }
                }

                if(!docFound){
                    //add new document entry
                    wordPrevValues.insert(docID + " " + to_string(pos));
                }
            }
        }
    }
}

set<string>& InvertedIndex::search(const string& word) const{
    return invertedMap->search(word);
}

set<string> InvertedIndex::searchPhrase(const string& phrase) const{
    stringstream ss(phrase);
    vector<string> phraseWords;
    string word;
    while(ss >> word){
        phraseWords.push_back(word);
    }

    //single word phrase
    if(phrase.size() == 1){
        return this->search(phraseWords[0]);
    }

    set<string> firstWordValue = this->search(phraseWords[0]);
    set<string> results;

    for(const string& docEntry : firstWordValue){
        int firstSpacePos = docEntry.find(' ');
        string docID = docEntry.substr(0, firstSpacePos);

        stringstream ss(docEntry.substr(firstSpacePos + 1));
        vector<int> positionsOfWordInDoc;
        int pos;
        while(ss >> pos){
            positionsOfWordInDoc.push_back(pos);
        }

        //check the phrase in this doc
        bool isPhrase = true;
        for(int i=1; i < phraseWords.size(); i++){
            set<string> nextWordValue = this->search(phraseWords[i]);
            bool isInTheDoc = false;

            for(const string& nextWordDocEntry : nextWordValue){
                int firstSpacePos = nextWordDocEntry.find(' ');
                string nextWordDocID = nextWordDocEntry.substr(0, firstSpacePos);

                if(nextWordDocID == docID){
                    stringstream ss(nextWordDocEntry.substr(firstSpacePos + 1));
                    vector<int> nextWordPositions;
                    int pos;
                    while(ss >> pos)
                        nextWordPositions.push_back(pos);

                    for(int firstWordPos : positionsOfWordInDoc){
                        if(find(nextWordPositions.begin(), nextWordPositions.end(), firstWordPos + i) != nextWordPositions.end()){
                            isInTheDoc = true;
                            break;
                        }
                    }

                    if(isInTheDoc)
                        break;
                }
            }

            if(!isInTheDoc){
                isPhrase = false;
                break;
            }
        }

        if(isPhrase){
            results.insert(docID);
        }

    }

    return results;
}