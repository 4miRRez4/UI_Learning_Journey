#include "user.h"
#include <fstream>
#include <sstream>
#include <vector>
std::vector<user> loadUser(const std::string &fileName){

    std::vector<user> users;
    std::ifstream file(fileName);

    if(file.is_open()){
        std::string line;
        while(getline(file,line)){
            std::stringstream ss(line);
            std::string firstName, lastName, username,password, phoneNumber, scorestr,maxScoreS;
            int score,maxScore;

            getline(ss,firstName,',');
            getline(ss,lastName,',');
            getline(ss,username,',');
            getline(ss,password,',');
            getline(ss,phoneNumber,',');
            getline(ss,scorestr,',');
            score = std::stoi(scorestr);
            getline(ss,maxScoreS,',');
            maxScore = std::stoi(maxScoreS);
            users.emplace_back(firstName, lastName, username,password, phoneNumber, score, maxScore);


        }
        file.close();
    }
    return users;
}
void saveUser(const std::string &fileName,const user &user){
    std::ofstream file(fileName, std::ios::app);
    if(file.is_open()){
        file << user.getName() << ","
             << user.getLastName() << ","
             << user.getUsername() << ","
             << user.getPassword() << ","
             << user.getPhone() << ","
             << user.getScore() << ","
             << "0\n";
        file.close();
    }

}

