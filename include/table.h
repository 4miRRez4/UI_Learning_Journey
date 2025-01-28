#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "map.h"
#include "BPlusTree.h"
#include "User.h"


class Table {
public:
    enum class DataType { INT, STRING, DATE };
    enum IndexType {PRIMARY, UNIQUE, NON_UNIQUE};

    struct Column {
        string name;
        DataType type;
        IndexType indexType;

        Column(string n, DataType t, IndexType it) : name(n), type(t), indexType(it) {}
    };

private:
    BPlusTree<int>* primaryIndex;
    Map<string, BPlusTree<string>*> uniqueIndexes;
    Map<string, BPlusTree<string>*> nonUniqueIndexes;

    vector<Column> columns; //col name and data type
    Map<int, vector<string>>* recordsMap; //primary key to row data


public: 
    Table(const vector<Column>& cols, int degree=2);
    ~Table();

    void addRecord(int id, const vector<string>& values);
    void removeRecord(int id);
    vector<string> searchRecord(int id);
    void updateRecord(int id, const vector<string>& newValues);
    bool containsRecord(int id) const;

    const vector<Column>& getColumns() const;

    void createIndex(string colName, IndexType it, int degree);

    void printAll() const;
};

#endif
