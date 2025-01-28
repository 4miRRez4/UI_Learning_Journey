#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "map.h"
#include "BPlusTree.h"
#include "User.h"

class Table {
private:
    struct Column {
        string name;
        Database::DataType type;
    };

    vector<Column> columns; //col name and data type
    BPlusTree<int>* index;
    Map<int, vector<string>>* recordsMap; //primary key to row data


public: 
    Table(const vector<pair<string, Database::DataType>>& cols, int degree=2);
    ~Table();

    void addRecord(int id, const vector<string>& values);
    void removeRecord(int id);
    vector<string> searchRecord(int id);
    void updateRecord(int id, const vector<string>& newValues);
    bool containsRecord(int id) const;

    const vector<Column>& getColumns() const;

    void printAll() const;
};

#endif
