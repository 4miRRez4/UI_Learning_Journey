#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10000000*1.3 + 7;

struct BucketChainNode{
    string key;
    vector<string> value;
    BucketChainNode* nextNode;

    BucketChainNode(const string& k, const vector<string> val): key(k), value(val), nextNode(nullptr) {}
};

class Map{
private: 
    BucketChainNode* table[TABLE_SIZE];

    int hashFunction(const string& key) const;
public:
    Map();
    ~Map();

    void insert(const string& key, const vector<string>& value);
    bool remove(const string& key);
    vector<string> search(const string& key) const;
};

#endif