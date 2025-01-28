#include "../include/table.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <climits>


Table::Table(int degree) {
    index = new BPlusTree<int>(degree);
    usersMap = new Map<int, User*>();
}

Table::~Table() {
    delete index;
    delete usersMap;
}

void Table::addUser(User* user) {
    int id = stoi(user->getId());

    if (usersMap->contains(id)) {
        cerr << "user with Id " << id << " already exists in the map." << endl;
        return;
    }

    index->insert(id); 

    usersMap->insert(id, user);
    cout << "user with Id " << id << " added successfully." << endl;
}


void Table::removeUser(int id) {
    if (!usersMap->contains(id)) {
        cerr << "user with Id " << id << " does not exist." << endl;
        return;
    }

    index->remove(id); 

    usersMap->remove(id); 
    cout << "user with ID " << id << " removed successfully." << endl;
}

User* Table::searchUser(int id) {
    if (!usersMap->contains(id)) {
        cerr << "user with Id " << id << " not found." << endl;;
        return nullptr;
    }
    return usersMap->search(id);
}

void Table::updateUser(int id, User* updatedUser) {
    if (!usersMap->contains(id)) {
        cerr << "user with Id " << id << " does not exist." << endl;
        return;
    }

    usersMap->insert(id, updatedUser); 
    cout << "user with Id " << id << " updated successfully." << endl;
}

void Table::printAll() const {
    cout << "All users in the database: " << endl;

    vector<int> allIds = index->rangeQuery(0, INT_MAX);
    for (int id : allIds) {
        try {
            User* user = usersMap->search(id);
            cout << user->getName();
        } catch (const std::exception& e) {
            cerr << "Error for user with ID " << id << ": " << e.what() << endl;
        }
    }
}

bool Table::containsUser(int userId) const {
    return usersMap->contains(userId);
}
