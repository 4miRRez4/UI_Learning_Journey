#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "map.h"
#include "BPlusTree.h"
#include "User.h"
#include <variant>

using Value = variant<int, string, double>;


class Table {
public:
    enum DataType { INT, STRING, DATE, DOUBLE };
    enum IndexType { PRIMARY, UNIQUE, NON_UNIQUE };

    struct Column {
        string name;
        DataType type;
        IndexType indexType;

        Column(string n, DataType t, IndexType it) : name(n), type(t), indexType(it) {}
    };

    struct Record {
        int id;          
        vector<Value> rowData;
    };

    string name;

private:
    int nextRecordId;
    BPlusTree<int>* primaryIndex;
    Map<string, BPlusTree<string>*> uniqueIndexes;
    Map<string, BPlusTree<string>*> nonUniqueIndexes;

    vector<Column> columns;
    Map<int, Record>* recordsMap; //primary key to row data


public: 
    Table(string name, const vector<Column>& cols, int nr_id=1, int degree=2);
    ~Table();

    void addRecord(const vector<Value>& values, int id=-1);
    void removeRecord(int id);
    Record searchRecord(int id);
    void updateRecord(int id, const vector<Value>& newValues);
    bool containsRecord(int id) const;
    int countRecords() const;
    vector<string> aggregate(string colName, const function<string(const vector<Value>&)>& aggFunc) const;
    vector<string> groupBy(string colName, const function<string(const vector<Value>&)>& aggFunc) const;

    const vector<Column>& getColumns() const;

    void createIndex(string colName, IndexType it, int degree);

    void printAll() const;
};

#endif
