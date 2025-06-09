#include "../include/JSONReader.h"

JSONReader::JSONReader(string f) : fileName(f) {}
vector<User> JSONReader::readUsers()
{
    vector<User> users;
    ifstream file(fileName);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        perror("Error opening file");
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

void JSONReader::writeUsers(const vector<User> &users)
{
    nlohmann::ordered_json jsonData; // استفاده از ordered_json برای حفظ ترتیب فیلدها

    for (const User &user : users)
    {
        nlohmann::ordered_json userData;
        userData["id"] = user.getId();
        userData["name"] = user.getName();
        userData["dateOfBirth"] = user.getDateOfBirth();
        userData["universityLocation"] = user.getUniversityLocation();
        userData["field"] = user.getField();
        userData["workplace"] = user.getWorkplace();
        userData["specialties"] = user.getSpecialties();
        userData["connectionId"] = user.getConnections();
        jsonData.push_back(userData); // حفظ ترتیب کاربران
    }
    ofstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }
    file << jsonData.dump(4); // ذخیره با فرمت مرتب‌شده
    file.close();
}
JSONReader::~JSONReader()
{
}
