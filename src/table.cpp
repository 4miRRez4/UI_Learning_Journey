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
    columns = cols;
}

Table::~Table() {
    delete primaryIndex;
    delete recordsMap;
    uniqueIndexes.iterate([](string col, IndexVariant& index) {
        visit([](auto&& ind) { delete ind; }, index);
    });
    nonUniqueIndexes.iterate([](string col, IndexVariant& index) {
        visit([](auto&& ind) { delete ind; }, index);
    });
}

int Table::countRecords() const {
    return primaryIndex->countKeys();
}
bool Table::isColumnIndexed(string colName) const{
    return indexedColumns.find(colName) != indexedColumns.end();
}

string Table::ValueToStr(const Value& val){
    string stred_val;
    if (holds_alternative<string>(val)) {
        stred_val = get<string>(val);
    } else if (holds_alternative<int>(val)) {
        stred_val = to_string(get<int>(val));
    } else if (holds_alternative<double>(val)) {
        stred_val = to_string(get<double>(val));
    } else if (holds_alternative<Date>(val)) {
        stred_val = get<Date>(val).toString();
    }
    return stred_val;

}

Value Table::strToValue(string input, DataType colType) {
    Value val;

    if (colType == DataType::INT) {
        try {
            int intValue = stoi(input); 
            val = intValue;
        } catch (const invalid_argument& e) {
            cout << "Invalid integer input." << endl;
            val = 0;
        }
    } else if (colType == DataType::DOUBLE) {
        try {
            double doubleValue = stod(input);
            val = doubleValue;
        } catch (const invalid_argument& e) {
            cerr << "Invalid double input." << endl;
            val = 0.0;
        }
    } else if (colType == DataType::STRING) {
        val = input; 
    } else if (colType == DataType::DATE) {
        try {
            int day, month, year;
            char slash1, slash2;
            istringstream iss(input);
            iss >> day >> slash1 >> month >> slash2 >> year;

            if (slash1 == '/' && slash1 == '/' && day >= 1 && day <= 31 && month >= 1 && month <= 12) {
                val = Date{year, month, day}; 
            } else {
                throw invalid_argument("Invalid date format.");
            }
        } catch (const exception& e) {
            cerr << "Invalid date input." << endl;
            val = Date{1111, 11, 11}; 
        }
    } else {
        cerr << "Invalid input data type." << endl;
        val = string{};
    }

    return val;
}


void Table::updateIndex(Map<string, IndexVariant>& indexMap, string colName, Value value, bool isInsert) {
    if (!indexMap.contains(colName)) return;  

    auto& indexVar = indexMap.search(colName);

    if (auto index = get_if<BPlusTree<int>*>(&indexVar)) {
        if (isInsert) (*index)->insert(get<int>(value));
        else (*index)->remove(get<int>(value));
    } 
    else if (auto index = get_if<BPlusTree<double>*>(&indexVar)) {
        if (isInsert) (*index)->insert(get<double>(value));
        else (*index)->remove(get<double>(value));
    } 
    else if (auto index = get_if<BPlusTree<Date>*>(&indexVar)) {
        if (isInsert) (*index)->insert(get<Date>(value));
        else (*index)->remove(get<Date>(value));
    } 
    else if (auto index = get_if<BPlusTree<string>*>(&indexVar)) {
        if (isInsert) (*index)->insert(get<string>(value));
        else (*index)->remove(get<string>(value));
    }
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
        updateIndex(uniqueIndexes, colName, values[i], true);
        updateIndex(nonUniqueIndexes, colName, values[i], true);    
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
        updateIndex(uniqueIndexes, colName, record.rowData[i], false);
        updateIndex(nonUniqueIndexes, colName, record.rowData[i], false);
    }

    recordsMap->remove(id); 

    cout << "Record with ID " << id << " removed successfully." << endl;
}

Table::Record Table::searchRecordById(int id) {
    if (!recordsMap->contains(id)) {
        cerr << "Record with Id " << id << " not found." << endl;;
        return {id, {}};
    }
    return recordsMap->search(id);
}

vector<Value> Table::searchByColumn(string colName, Value value) {
    vector<Value> results;

    if (uniqueIndexes.contains(colName)) {
        auto& indexVar = uniqueIndexes.search(colName);

        if (auto index = get_if<BPlusTree<int>*>(&indexVar)) {
            if ((*index)->search(get<int>(value))) {
                results.push_back(value);
            }
        } 
        else if (auto index = get_if<BPlusTree<double>*>(&indexVar)) {
            if ((*index)->search(get<double>(value))) {
                results.push_back(value);
            }
        } 
        else if (auto index = get_if<BPlusTree<Date>*>(&indexVar)) {
            if ((*index)->search(get<Date>(value))) {
                results.push_back(value);
            }
        } 
        else if (auto index = get_if<BPlusTree<string>*>(&indexVar)) {
            if ((*index)->search(get<string>(value))) {
                results.push_back(value);
            }
        }
    } 
    else if (nonUniqueIndexes.contains(colName)) {
        auto& indexVar = nonUniqueIndexes.search(colName);

        if (auto index = get_if<BPlusTree<int>*>(&indexVar)) {
            vector<int> values = (*index)->rangeQuery(get<int>(value), get<int>(value));
            for (int v : values) results.push_back(v);
        } 
        else if (auto index = get_if<BPlusTree<double>*>(&indexVar)) {
            vector<double> values = (*index)->rangeQuery(get<double>(value), get<double>(value));
            for (double v : values) results.push_back(v);
        } 
        else if (auto index = get_if<BPlusTree<Date>*>(&indexVar)) {
            vector<Date> values = (*index)->rangeQuery(get<Date>(value), get<Date>(value));
            for (const Date& v : values) results.push_back(v);
        } 
        else if (auto index = get_if<BPlusTree<string>*>(&indexVar)) {
            vector<string> values = (*index)->rangeQuery(get<string>(value), get<string>(value));
            for (const string& v : values) results.push_back(v);
        }
    } 
    else {  
        cout << "No index found for column: " << colName << endl;
    }

    return results;
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
    cout << "Record with ID " << id << " updated successfully." << endl;
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

void Table::createIndex(string colName, IndexType indexType, int degree) {
    for (int i=0; i<columns.size(); i++) {
        const auto& col = columns[i];
        if (col.name == colName) {
            if (indexType == IndexType::UNIQUE) {
                if (uniqueIndexes.contains(colName)) {
                    cout << "Unique index already exists for column: " + colName << endl;
                    return;
                }
                
                if (col.type == DataType::INT) {
                    uniqueIndexes.insert(colName, new BPlusTree<int>(degree));
                } 
                else if (col.type == DataType::DOUBLE) {
                    uniqueIndexes.insert(colName, new BPlusTree<double>(degree));
                } 
                else if (col.type == DataType::DATE) {
                    uniqueIndexes.insert(colName, new BPlusTree<Date>(degree));
                } 
                else {
                    uniqueIndexes.insert(colName, new BPlusTree<string>(degree));
                }
            } 
            else if (indexType == IndexType::NON_UNIQUE) {
                if (nonUniqueIndexes.contains(colName)) {
                    cout << "Non-unique index already exists for column: " + colName << endl;
                    return;
                }
                
                if (col.type == DataType::INT) {
                    nonUniqueIndexes.insert(colName, new BPlusTree<int>(degree));
                } 
                else if (col.type == DataType::DOUBLE) {
                    nonUniqueIndexes.insert(colName, new BPlusTree<double>(degree));
                } 
                else if (col.type == DataType::DATE) {
                    nonUniqueIndexes.insert(colName, new BPlusTree<Date>(degree));
                } 
                else {
                    nonUniqueIndexes.insert(colName, new BPlusTree<string>(degree));
                }
            }

            indexedColumns.insert(colName);  

            //filling new index
            recordsMap->iterate([&](int id, const Record& record) {
                Value value = record.rowData[i];

                if (indexType == IndexType::UNIQUE) {
                    auto& indexVar = uniqueIndexes.search(colName);

                    if (auto index = get_if<BPlusTree<int>*>(&indexVar)) {
                        if (!(*index)->search(get<int>(value))) 
                            (*index)->insert(get<int>(value));
                    } 
                    else if (auto index = get_if<BPlusTree<double>*>(&indexVar)) {
                        if (!(*index)->search(get<double>(value))) 
                            (*index)->insert(get<double>(value));
                    } 
                    else if (auto index = get_if<BPlusTree<Date>*>(&indexVar)) {
                        if (!(*index)->search(get<Date>(value))) 
                            (*index)->insert(get<Date>(value));
                    } 
                    else if (auto index = get_if<BPlusTree<string>*>(&indexVar)) {
                        if (!(*index)->search(get<string>(value))) 
                            (*index)->insert(get<string>(value));
                    }
                } 
                else if (indexType == IndexType::NON_UNIQUE) {
                    auto& indexVar = nonUniqueIndexes.search(colName);

                    if (auto index = get_if<BPlusTree<int>*>(&indexVar)) {
                        (*index)->insert(get<int>(value));
                    } 
                    else if (auto index = get_if<BPlusTree<double>*>(&indexVar)) {
                        (*index)->insert(get<double>(value));
                    } 
                    else if (auto index = get_if<BPlusTree<Date>*>(&indexVar)) {
                        (*index)->insert(get<Date>(value));
                    } 
                    else if (auto index = get_if<BPlusTree<string>*>(&indexVar)) {
                        (*index)->insert(get<string>(value));
                    }
                }
            });

            cout << "Index created for column: " << colName << " successfuly." << endl;
            return;
        }
    }
    cout << "Column not found: " + colName << endl;
}


void Table::printAll() {
    cout << "All records in Table:" << endl;

    recordsMap->iterate([&](int id, const Record& record) {
        cout << "ID: " << id << " => ";
        for (int i = 0; i < record.rowData.size(); ++i) {
            string stred_val = ValueToStr(record.rowData[i]);
            cout << columns[i].name << ": " << stred_val << " ";
        }
        cout << endl;
    });
}
