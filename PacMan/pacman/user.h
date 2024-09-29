#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include <vector>
class user
{
public:

    user() : username(""), password(""), name(""), lastname(""), phone(""), score(0), maxScore(0) {}

    user(const std::string& name,const std::string& lastname,const std::string username,
         const std::string password,const std::string phone, int score, int maxScore)
        : name(name), lastname(lastname), username(username),
        password(password), phone(phone), score(score){}

    const std::string getName() const {return name;}
    const std::string getLastName() const {return lastname;}
    const std::string getUsername()const {return username;}
    const std::string getPassword() const {return password;}
    const std::string getPhone() const {return phone;}
    int getScore() const {return score;}
    int getMaxScore() const {return maxScore;}
    void setScore(int newScore) { score = newScore;}
private:
    std::string name;
    std::string lastname;
    std::string username;
    std::string password;
    std::string phone;
    int score;
    int maxScore;
};

std::vector<user> loadUser(const std::string& fileName);
void saveUser(const std::string& fileName,const user& user);

#endif // USER_H
