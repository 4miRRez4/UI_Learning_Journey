#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "map.h"
#include "BPlusTree.h"
#include "user.h"

class Table {
private:
    BPlusTree<int> index;
    Map<int, User> usersMap; 

public:
    Table(int degree=2);
    ~Table() = default;

    void addUser(const User& user);
    void removeUser(int id);
    User* searchUser(int id);
    void updateUser(int id, const User& updatedUser);

    bool containsUser(int id) const;

    void printAll() const;
};

#endif
