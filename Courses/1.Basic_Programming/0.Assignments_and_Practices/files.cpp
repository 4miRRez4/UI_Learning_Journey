#include <iostream>
#include <fstream>

using namespace std;

struct player
{
    char name[50];
    char password[50];
    int score;
};

bool save_to_file(player &p, char *file_path)
{
    ofstream file;

    file.open(file_path, ios::binary);

    if (!file.is_open())
    {
        cout << "Error!" << endl;
        return false;
    }

    file.write((char *)&p, sizeof(player));
    return true;
}

bool load_from_file(player &p, char *file_path)
{
    ifstream file;

    file.open(file_path, ios::binary);

    if (!file.is_open())
    {
        cout << "Error!" << endl;
        return false;
    }

    file.read((char *)&p, sizeof(player));
    return true;
}

int main()
{
    // player p1;
    // cout << "Enter name, score, pass" << endl;
    // cin >> p1.name;
    // cin >> p1.score;
    // cin >> p1.password;

    // save_to_file(p1, "player.dat");

    player p2;

    if(load_from_file(p2, "player.dat"))
        cout << "File opened";

    cout << p2.name << endl;
    cout << p2.password << endl;
    cout << p2.score << endl;


}