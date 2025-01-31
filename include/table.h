#ifndef TABLE_H
#define TABLE_H

#include "map.h"
#include "BPlusTree.h"
#include "User.h"
#include "date.h"
#include <string>
#include <vector>
#include <set>
#include <variant>

using Value = variant<int, double, string, Date>;
using IndexVariant = variant<BPlusTree<int>*, BPlusTree<double>*, BPlusTree<string>*, BPlusTree<Date>*>;


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

    set<string> indexedColumns;
    BPlusTree<int>* primaryIndex;
    Map<string, IndexVariant> uniqueIndexes;
    Map<string, IndexVariant> nonUniqueIndexes;

    vector<Column> columns;
    Map<int, Record>* recordsMap; //primary key to row data


public: 
    Table(string name, const vector<Column>& cols, int nr_id=1, int degree=2);
    ~Table();

    void setNextRecordId(int nextId);
    void addRecord(const vector<Value>& values, int id=-1);
    void removeRecord(int id);
    Record searchRecordById(int id);
    vector<Value> searchByColumn(string colName, Value value);
    void updateRecord(int id, const vector<Value>& newValues);
    bool containsRecord(int id) const;
    int countRecords() const;
    string ValueToStr(const Value& val);
    Value strToValue(string input, DataType colType);
    vector<string> aggregate(string colName, const function<string(const vector<Value>&)>& aggFunc) const;
    const vector<Column>& getColumns() const;
    void createIndex(string colName, IndexType it, int degree);
    bool isColumnIndexed(string colName) const;
    void updateIndex(Map<string, IndexVariant>& indexMap, string colName, Value value, bool isInsert);


    void printAll() ;
};

#endif
