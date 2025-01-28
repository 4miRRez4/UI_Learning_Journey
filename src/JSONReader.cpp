#include "../include/JSONReader.h"

JSONReader::JSONReader(string f) : fileName(f) {}
vector<User> JSONReader::readUsers()
{
    vector<User> users;
    ifstream file(fileName);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return users;
    }
    json jsonData;
    file >> jsonData;
    for (auto &userData : jsonData)
    {
        string id = userData["id"];
        string name = userData["name"];
        string dateOfBirth = userData["dateOfBirth"];
        string universityLocation = userData["universityLocation"];
        string field = userData["field"];
        string workplace = userData["workplace"];
        vector<string> specialties = userData["specialties"];
        vector<string> connectionIds = userData["connectionId"];
        User user(id, name, dateOfBirth, universityLocation, field, workplace, specialties, connectionIds);
        users.push_back(user);
    }
    file.close();
    return users;
}

JSONReader::~JSONReader()
{
}
