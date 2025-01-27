#ifndef USER_H
#define USER_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class User
{
public:
    User(string id, string name, string dateOfBirth, string univesity, string field, string wordPlac, vector<string> specialties, vector<string> connectionIds)
        : id(id),
          name(name),
          dateOfBirth(dateOfBirth),
          universityLocation(univesity),
          field(field),
          workplace(wordPlac),
          specialties(specialties),
          connectionIds(connectionIds) {}

    string getId() const;
    string getName() const;
    string getDateOfBirth() const;
    string getUniversityLocation() const;
    string getField() const;
    string getWorkplace() const;
    const vector<string> &getSpecialties() const;
    const vector<string> &getConnections() const;

private:
    string id;
    string name;
    string dateOfBirth;
    string universityLocation;
    string field;
    string workplace;
    vector<string> specialties;
    vector<string> connectionIds;
};

#endif