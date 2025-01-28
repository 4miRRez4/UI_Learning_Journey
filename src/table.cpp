#include "../include/dataBase.h"
#include <iostream>
#include <stdexcept>
#include <vector>


Database::Database(int degree) : index(degree) {}

void Database::addUser(const User& user) {
    int id = stoi(user.getId());

    if (usersMap.contains(id)) {
        cerr << "user with Id " << id << " already exists in the map." << endl;
        return;
    }

    index.insert(id); 

    usersMap.insert(id, user);
    cout << "user with Id " << id << " added successfully." << endl;
}


void Database::removeUser(int id) {
    if (!usersMap.contains(id)) {
        cerr << "user with Id " << id << " does not exist." << endl;
        return;
    }

    index.remove(id); 

    usersMap.remove(id); 
    cout << "user with ID " << userId << " removed successfully." << endl;
}

User* Database::searchUser(int id) {
    if (!usersMap.contains(id)) {
        cerr << "user with Id " << id << " not found." << endl;;
        return nullptr;
    }
    return &usersMap.search(id);
}

void Database::updateUser(int id, const User& updatedUser) {
    if (!usersMap.contains(id)) {
        cerr << "user with Id " << id << " does not exist." << endl;
        return;
    }

    usersMap.insert(id, updatedUser); 
    cout << "user with Id " << id << " updated successfully." << endl;
}

void Database::printAll() const {
    cout << "All users in the database: " << endl;

    vector<int> allIds = index.rangeQuery(0, INT_MAX);
    for (int id : allIds) {
        try {
            const User& user = usersMap.search(id);
            user.printUser();
        } catch (const std::exception& e) {
            cerr << "Error for user with ID " << id << ": " << e.what() << endl;
        }
    }
}

bool Database::containsUser(int userId) const {
    return usersMap.contains(userId);
}
