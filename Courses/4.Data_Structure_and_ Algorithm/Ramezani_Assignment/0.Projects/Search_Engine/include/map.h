#ifndef MAP_H
#define MAP_H

#include <string>
#include <set>
using namespace std;

const int TABLE_SIZE = 10000000*1.3 + 7;

struct BucketChainNode{
    string key;
    set<string> value;
    BucketChainNode* nextNode;

    BucketChainNode(const string& k, const set<string> val): key(k), value(val), nextNode(nullptr) {}
};

class Map{
private: 
    BucketChainNode* table[TABLE_SIZE];

    int hashFunction(const string& key) const;
public:
    Map();
    ~Map();

    void insert(const string& key, const set<string>& value);
    bool remove(const string& key);
    set<string>& search(const string& key) const;
};

#endif