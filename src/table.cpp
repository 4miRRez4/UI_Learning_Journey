#include "../include/table.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <climits>


Table::Table(string name, const vector<Column>& cols, int nr_id, int degree) {
    this->name = name;
    this->nextRecordId = nr_id;

    recordsMap = new Map<int, Record>();
    primaryIndex = new BPlusTree<int>(degree);

    for (const auto& col : cols) {
        columns.push_back(col);

        if (col.indexType == IndexType::UNIQUE) {
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

void Table::addRecord(const vector<Value>& values, int id) {
    if (values.size() != columns.size()) {
        cerr << "Invalid values sizes." << endl;
        return;
    }

    if (id == -1){
        id = nextRecordId++;
    }

    if (this->containsRecord(id)) {
        cerr << "record with Id " << id << " already exists in the map." << endl;
        return;
    }

    if (primaryIndex->search(id)) {
        throw runtime_error("Duplicated key for primary index.");
    }
    primaryIndex->insert(id);

    for (int i = 0; i < values.size(); ++i) {
        string colName = columns[i].name;
        string stred_val;
        if (holds_alternative<string>(values[i])) {
            stred_val = get<string>(values[i]);
        } else if (holds_alternative<int>(values[i])) {
            stred_val = to_string(get<int>(values[i]));
        } else if (holds_alternative<double>(values[i])) {
            stred_val = to_string(get<double>(values[i]));
}
        if (columns[i].indexType == UNIQUE) {
            if (!uniqueIndexes.contains(colName)) {
                cerr << "Unique index not found for column: " << colName << endl;
                return;
            }
            if (uniqueIndexes.search(colName)->search(stred_val)) {
                throw runtime_error("Duplicated value for unique index on column: " + colName);
            }

            uniqueIndexes.search(colName)->insert(stred_val);
        } 
        else if (columns[i].indexType == NON_UNIQUE) {
            if (!nonUniqueIndexes.contains(colName)) {
                cerr << "Non-unique index not found for column: " << colName << endl;
                return;
            }

            nonUniqueIndexes.search(colName)->insert(stred_val);
        }
    }

    recordsMap->insert(id, {id, values});

    cout << "record with Id " << id << " added successfully." << endl;
}


void Table::removeRecord(int id) {
    if (!recordsMap->contains(id)) {
        cerr << "record with Id " << id << " does not exist." << endl;
        return;
    }

    primaryIndex->remove(id); 

    Record record = recordsMap->search(id);
    for (int i = 0; i < record.rowData.size(); ++i) {
        string colName = columns[i].name;
        string value;
        if (holds_alternative<string>(record.rowData[i])) {
            value = get<string>(record.rowData[i]);
        } else if (holds_alternative<int>(record.rowData[i])) {
            value = to_string(get<int>(record.rowData[i]));
        } else if (holds_alternative<double>(record.rowData[i])) {
            value = to_string(get<double>(record.rowData[i]));
}

        if (uniqueIndexes.contains(colName)) {
            uniqueIndexes.search(colName)->remove(value);
        } else if (nonUniqueIndexes.contains(colName)) {
            nonUniqueIndexes.search(colName)->remove(value);
        }
    }


    recordsMap->remove(id); 

    cout << "Record with ID " << id << " removed successfully." << endl;
}

Table::Record Table::searchRecord(int id) {
    if (!recordsMap->contains(id)) {
        cerr << "Record with Id " << id << " not found." << endl;;
        return {id, {}};
    }
    return recordsMap->search(id);
}

void Table::updateRecord(int id, const vector<Value>& newValues) {
    if (!recordsMap->contains(id)) {
        cerr << "Record with ID " << id << " does not exist." << endl;
        return;
    }

    if (newValues.size() != columns.size()) {
        cerr << "Invalid values size.";
        return;
    }

    removeRecord(id);

    addRecord(newValues, id);
    cout << "Record with ID " << id << " updated successfully.\n";
}


bool Table::containsRecord(int id) const {
    return recordsMap->contains(id);
}

const vector<Table::Column>& Table::getColumns() const{
    return columns;
}

vector<string> Table::aggregate(string colName, const function<string(const vector<Value>&)>& aggFunc) const {
    vector<Value> colValues;

    recordsMap->iterate([&](int id, const Record& record) {
        auto col_it = find_if(columns.begin(), columns.end(), [&](const Column& col) { return col.name == colName; });
        int colInd = distance(columns.begin(), col_it);

        if (colInd < record.rowData.size()) {
            colValues.push_back(record.rowData[colInd]);
        }
    });

    return {aggFunc(colValues)};
}

vector<string> Table::groupBy(string colName, const function<string(const vector<Value>&)>& aggFunc) const {
    unordered_map<string, vector<Value>> groupedValues;

    recordsMap->iterate([&](int id, const Record& record) {
        auto col_it = find_if(columns.begin(), columns.end(), [&](const Column& col) { return col.name == colName; });
        int colIndex = distance(columns.begin(), col_it);

        if (colIndex < record.rowData.size()) {
            string key;
            if (holds_alternative<int>(record.rowData[colIndex])) {
                key = to_string(get<int>(record.rowData[colIndex]));
            } else if (holds_alternative<double>(record.rowData[colIndex])) {
                key = to_string(get<double>(record.rowData[colIndex]));
            } else {
                key = get<string>(record.rowData[colIndex]);
            }

            groupedValues[key].push_back(record.rowData[colIndex]);
        }
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

    recordsMap->iterate([&](int id, const Record& record) {
        cout << "ID: " << id << " => ";
        for (int i = 0; i < record.rowData.size(); ++i) {
            if (holds_alternative<int>(record.rowData[i])) {
                cout << columns[i].name << ": " << get<int>(record.rowData[i]) << " ";
            } else if (holds_alternative<string>(record.rowData[i])) {
                cout << columns[i].name << ": " << get<string>(record.rowData[i]) << " ";
            } else if (holds_alternative<double>(record.rowData[i])) {
                cout << columns[i].name << ": " << get<double>(record.rowData[i]) << " ";
            }
        }
        cout << endl;
    });
}
