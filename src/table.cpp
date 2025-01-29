#include "../include/table.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <climits>


Table::Table(const vector<Column>& cols, int degree) {
    recordsMap = new Map<int, vector<string>>();

    for (const auto& col : cols) {
        columns.push_back(col);

        if (col.indexType == IndexType::PRIMARY) {
            if (primaryIndex) {
                throw runtime_error("Primary index already exists.");
            }
            primaryIndex = new BPlusTree<int>(degree);
        } 
        else if (col.indexType == IndexType::UNIQUE) {
            if (uniqueIndexes.contains(col.name)) {
                throw runtime_error("Unique index already exists for column: " + col.name);
            }
            uniqueIndexes.insert(col.name, new BPlusTree<string>(degree));
        } 
        else if (col.indexType == IndexType::NON_UNIQUE) {
            if (nonUniqueIndexes.contains(col.name)) {
                throw runtime_error("Non-unique index already exists for column: " + col.name);
            }
            nonUniqueIndexes.insert(col.name, new BPlusTree<string>(degree));
        }
    }
}

Table::~Table() {
    delete primaryIndex;
    delete recordsMap;
    uniqueIndexes.iterate([](string col, BPlusTree<string>* ind) {
        delete ind; 
    });
    nonUniqueIndexes.iterate([](string col, BPlusTree<string>* ind) {
        delete ind; 
    });
}

int Table::countRecords() const {
    return primaryIndex->countKeys();
}

void Table::addRecord(int id, const vector<string>& values) {
    if (values.size() != columns.size()) {
        cerr << "Invalid values sizes." << endl;
        return;
    }
    if (recordsMap->contains(id)) {
        cerr << "record with Id " << id << " already exists in the map." << endl;
        return;
    }

    if (primaryIndex->search(id)) {
        throw std::runtime_error("Duplicated key for primary index.");
    }
    primaryIndex->insert(id);

    for (int i = 0; i < values.size(); ++i) {
        string colName = columns[i].name;
        string value = values[i];

        if (columns[i].indexType == UNIQUE) {
            if (!uniqueIndexes.contains(colName)) {
                cerr << "Unique index not found for column: " << colName << endl;
                return;
            }
            if (uniqueIndexes.search(colName)->search(value)) {
                throw std::runtime_error("Duplicated value for unique index on column: " + colName);
            }

            uniqueIndexes.search(colName)->insert(value);
        } 
        else if (columns[i].indexType == NON_UNIQUE) {
            if (!nonUniqueIndexes.contains(colName)) {
                cerr << "Non-unique index not found for column: " << colName << endl;
                return;
            }

            nonUniqueIndexes.search(colName)->insert(value);
        }
    }

    recordsMap->insert(id, values);

    cout << "record with Id " << id << " added successfully." << endl;
}


void Table::removeRecord(int id) {
    if (!recordsMap->contains(id)) {
        cerr << "record with Id " << id << " does not exist." << endl;
        return;
    }

    primaryIndex->remove(id); 

    vector<string>& values = recordsMap->search(id);
    for (int i = 0; i < values.size(); ++i) {
        string colName = columns[i].name;
        string value = values[i];

        if (uniqueIndexes.contains(colName)) {
            uniqueIndexes.search(colName)->remove(value);
        } else if (nonUniqueIndexes.contains(colName)) {
            nonUniqueIndexes.search(colName)->remove(value);
        }
    }


    recordsMap->remove(id); 

    cout << "user with ID " << id << " removed successfully." << endl;
}

vector<string> Table::searchRecord(int id) {
    if (!recordsMap->contains(id)) {
        cerr << "user with Id " << id << " not found." << endl;;
        return {};
    }
    return recordsMap->search(id);
}

void Table::updateRecord(int id, const vector<string>& newValues) {
    removeRecord(id);  
    addRecord(id, newValues);
    cout << "user with Id " << id << " updated successfully." << endl;
}

void Table::printAll() const {
    cout << "All records in the database: " << endl;

    vector<int> allIds = primaryIndex->rangeQuery(0, INT_MAX);
    for (int id : allIds) {
        try {
            vector<string> rec = recordsMap->search(id);
            for(int i=0; i<rec.size(); i++){
                cout << rec[i] << endl;
            }

        } catch (const std::exception& e) {
            cerr << "Error for record with ID " << id << ": " << e.what() << endl;
        }
    }
}

bool Table::containsRecord(int id) const {
    return recordsMap->contains(id);
}

const vector<Table::Column>& Table::getColumns() const{
    return columns;
}

vector<string> Table::aggregate(string colName, const function<string(const vector<string>&)>& aggFunc) const {
    vector<string> colValues;

    recordsMap->iterate([&](int id, vector<string>& row) {
        auto col_it = find_if(columns.begin(), columns.end(), [&](const Column& col) { return col.name == colName; });
        int colInd = distance(columns.begin(), col_it);
        colValues.push_back(row[colInd]);
    });

    return {aggFunc(colValues)};
}

vector<string> Table::groupBy(string colName, const function<string(const vector<string>&)>& aggFunc) const {
    unordered_map<string, vector<string>> groupedValues;

    recordsMap->iterate([&](int id, vector<string>& row) {
        auto col_it = find_if(columns.begin(), columns.end(), [&](const Column& col) { return col.name == colName; });
        int colIndex = distance(columns.begin(), col_it);
        string key = row[colIndex];
        groupedValues[key].push_back(row[colIndex]);
    });

    vector<string> results;
    for (auto& [key, group] : groupedValues) {
        results.push_back(key + ": " + aggFunc(group));
    }

    return results;
}

void Table::createIndex(string colName, IndexType it, int degree) {
    for (const auto& col : columns) {
        if (col.name == colName) {
            if (it == IndexType::UNIQUE) {
                uniqueIndexes.insert(colName, new BPlusTree<string>(degree));
            } 
            else if (it == IndexType::NON_UNIQUE) {
                nonUniqueIndexes.insert(colName, new BPlusTree<string>(degree));
            }
            cout << "Index of column: " << colName << " created." << endl;
            return;
        }
    }
    throw runtime_error("Column not found.");
}

void Table::printAll() const {
    cout << "All records in Table:" << endl;

    recordsMap->iterate([&](int id, const vector<string>& values) {
        cout << "ID: " << id << " | ";
        for (int i = 0; i < values.size(); ++i) {
            cout << columns[i].name << ": " << values[i] << " ";
        }
        cout << endl;
    });
}
