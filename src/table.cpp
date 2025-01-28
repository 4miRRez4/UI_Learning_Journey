#include "../include/table.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <climits>


Table::Table(const vector<pair<string, DataType>>& cols, int degree) : columns(columns) {
    index = new BPlusTree<int>(degree);
    recordsMap = new Map<int, vector<string>>();

    for (const auto& col : cols) {
        columns.push_back({col.first, col.second});
    }
}

Table::~Table() {
    delete index;
    delete recordsMap;
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

    index->insert(id); 
    recordsMap->insert(id, values);

    cout << "record with Id " << id << " added successfully." << endl;
}


void Table::removeRecord(int id) {
    if (!recordsMap->contains(id)) {
        cerr << "record with Id " << id << " does not exist." << endl;
        return;
    }

    index->remove(id); 
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
    if (newValues.size() != columns.size()) {
        cerr << "Error: Number of values does not match the number of columns.\n";
        return;
    }
    if (!recordsMap->contains(id)) {
        cerr << "user with Id " << id << " does not exist." << endl;
        return;
    }

    recordsMap->insert(id, newValues); 

    cout << "user with Id " << id << " updated successfully." << endl;
}

void Table::printAll() const {
    cout << "All records in the database: " << endl;

    vector<int> allIds = index->rangeQuery(0, INT_MAX);
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
