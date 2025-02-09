#include "../include/User.h"

User::User(string id, string name, string dateOfBirth, string univesity, string field, string wordPlac, vector<string> specialties, vector<string> connectionIds)
    : id(id),
      name(name),
      dateOfBirth(dateOfBirth),
      universityLocation(univesity),
      field(field),
      workplace(wordPlac),
      specialties(specialties),
      connectionIds(connectionIds) {}

string User::getId() const
{
    return id;
}

string User::getName() const
{
    return name;
}

string User::getDateOfBirth() const
{
    return dateOfBirth;
}

string User::getUniversityLocation() const
{
    return universityLocation;
}

string User::getField() const
{
    return field;
}

string User::getWorkplace() const
{
    return workplace;
}

const vector<string> &User::getSpecialties() const
{
    return specialties;
}

const vector<string> &User::getConnections() const
{
    return connectionIds;
}

void User::addConnection(const string &connectionId)
{
    if (find(connectionIds.begin(), connectionIds.end(), connectionId) == connectionIds.end())
    {
        connectionIds.push_back(connectionId);
    }
}

void User::removeConnection(const string &connectionId)
{
    connectionIds.erase(
        remove(connectionIds.begin(), connectionIds.end(), connectionId),
        connectionIds.end());
}
