#ifndef JSONREADER_H
#define JSONREADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "User.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class JSONReader
{
public:
    JSONReader(string f);
    vector<User> readUsers();
    void writeUsers(const vector<User> &users);

    ~JSONReader();

private:
    string fileName;
};

#endif