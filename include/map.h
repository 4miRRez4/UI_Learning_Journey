#ifndef MAP_H
#define MAP_H

#include <stdexcept>
#include <functional>

const int TABLE_SIZE =  10000000*1.3 + 7;

template <typename K, typename V>
class Map {
private:
    struct BucketChainNode {
        K key;
        V value;
        BucketChainNode* nextNode;

        BucketChainNode(const K& k, const V& val) 
            : key(k), value(val), nextNode(nullptr) {}
    };

    BucketChainNode* table[TABLE_SIZE];

    int hashFunction(const K& key) const;

public:
    Map();
    ~Map();

    void insert(const K& key, const V& value);
    bool remove(const K& key);
    bool contains(const K& key) const;
    const V& search(const K& key) const;
};


template <typename K, typename V>
Map<K, V>::Map() {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
}

template <typename K, typename V>
Map<K, V>::~Map() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        BucketChainNode* curr = table[i];
        while (curr) {
            BucketChainNode* tmp = curr;
            curr = curr->nextNode;
            delete tmp;
        }
    }
}

template <typename K, typename V>
int Map<K, V>::hashFunction(const K& key) const {
    std::hash<K> hashFunc;
    return hashFunc(key) % TABLE_SIZE;
}

template <typename K, typename V>
void Map<K, V>::insert(const K& key, const V& value) {
    int hashInd = hashFunction(key);

    BucketChainNode* curr = table[hashInd];
    while (curr) {
        if (curr->key == key) {
            curr->value = value; // update existing value
            return;
        }
        curr = curr->nextNode;
    }

    // key doesn't exist, so create a new node
    BucketChainNode* newNode = new BucketChainNode(key, value);
    newNode->nextNode = table[hashInd];
    table[hashInd] = newNode;
}

template <typename K, typename V>
bool Map<K, V>::remove(const K& key) {
    int hashInd = hashFunction(key);
    BucketChainNode* curr = table[hashInd];
    BucketChainNode* prev = nullptr;

    while (curr) {
        if (curr->key == key) {
            if (prev)
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

template <typename K, typename V>
bool Map<K, V>::contains(const K& key) const {
    int hashInd = hashFunction(key);
    BucketChainNode* curr = table[hashInd];

    while (curr) {
        if (curr->key == key)
            return true;
        curr = curr->nextNode;
    }

    return false;
}

template <typename K, typename V>
const V& Map<K, V>::search(const K& key) const {
    int hashInd = hashFunction(key);
    BucketChainNode* curr = table[hashInd];

    while (curr) {
        if (curr->key == key)
            return curr->value;
        curr = curr->nextNode;
    }

    throw runtime_error("Key not found in the map.");
}

#endif
