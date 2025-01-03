#include "../include/map.h"

Map::Map(){
    for(int i=0; i<TABLE_SIZE; i++)
        table[i] = nullptr;
}

Map::~Map(){
    for(int i=0; i<TABLE_SIZE; i++){
        BucketChainNode* curr_buck = table[i];
        while(curr_buck){
            BucketChainNode* tmp = curr_buck;
            curr_buck = curr_buck->nextNode;
            delete curr_buck;
        }
    }
}

int Map::hashFunction(const string& key) const{
    unsigned long long hash = 0;
    unsigned long long primeNum = 31;

    for(int i=0; i<key.length(); i++)
        hash = (hash*primeNum + key[i]) % TABLE_SIZE;

    return static_cast<int>(hash);
}


void Map::insert(const string& key, const vector<string>& value){
    int hashInd = hashFunction(key);

    BucketChainNode* curr_buck = table[hashInd];
    while(curr_buck){
        if(curr_buck->key == key){
            curr_buck->value = value; //update existing value
            return;
        }
        curr_buck = curr_buck->nextNode;
    }

    //key doesn't exist so create new node
    BucketChainNode* newNode = new BucketChainNode(key, value);
    newNode->nextNode = table[hashInd];
    table[hashInd] = newNode;
}

bool Map::remove(const string& key){
    int hashInd = hashFunction(key);
    BucketChainNode* curr = table[hashInd];
    BucketChainNode* prev = nullptr;

    while(curr){
        if(curr->key == key){
            if(prev)
                prev->nextNode = curr->nextNode;
            else
                table[hashInd] = curr->nextNode;
            
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->nextNode;
    }

    return false;

}



vector<string>& Map::search(const string& key) const{
    int hashInd = hashFunction(key);
    BucketChainNode* curr = table[hashInd];

    while(curr){
        if(curr->key == key)
            return curr->value;

        curr = curr->nextNode;
    }

    static vector<string> empty;
    return empty;
}
