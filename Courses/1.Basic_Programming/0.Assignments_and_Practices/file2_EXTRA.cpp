#include <iostream>
#include <fstream>

using namespace std;

struct MyStruct
{
    int rank;
    char name[100];
    int score;
};

int main()
{
    MyStruct myArray[3] = {
        {1, "Ali", 3},
        {2, "Mamad", 2},
        {3, "Tina", 1}};

        std::ofstream outFile("data.txt", ios::out);

    if (!outFile.is_open())
    {
        cout << "Error opening the file." << endl;
        return 1; 
    }

    for (int i = 0; i < 3; ++i)
    {
        outFile << myArray[i].rank << " "
                << myArray[i].name << " "
                << myArray[i].score << endl;
    }

    outFile.close();

    std::cout << "Saved!" << std::endl;

    // load
    MyStruct myArray2[3];

    std::ifstream inFile("data.txt", ios::in);

    if (!inFile.is_open())
    {
        cout << "Error opening the file." << endl;
        return 1; 
    }

    for (int i = 0; i < 3; ++i)
    {
        inFile >> myArray2[i].rank
               >> myArray2[i].name
               >> myArray2[i].score;
    }

    return 0;
}
