#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

string encoder(string message){

	int numberOfElements = message.length() / 4;
	if(message.length() % 4 != 0) numberOfElements++;

    int encriptedArr[numberOfElements] = {};
    int arrInd = -1;
    for(int c=0; c<message.length(); c++)
    {
        int asciiCode = message[c];
        if(c%4 == 0) 
            arrInd++;
        encriptedArr[arrInd] = encriptedArr[arrInd] | (asciiCode << 8*(c%4));
    }


    string answer = "";
    answer += to_string(numberOfElements) + "\n";
    for(int i=0; i<numberOfElements; i++)
        answer += to_string(encriptedArr[i]) + "\n";

    return answer;
}

string generateRandomString(int len) {
    string result="";
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&* ";
    int size = sizeof(characters) - 1;

    for (int i = 0; i < len; ++i) {
        result += characters[rand() % size];
    }

    return result;
}


void generateTestCase(string inFileName, string outFileName) {
    FILE* inFile = fopen(inFileName.c_str(), "w");
    if (!inFile) {
        cerr << "Error: Could not open file " << inFileName << " for writing." << endl;
        return;
    }

    int randLength = 1 + rand() % 1000;
    string randStr = generateRandomString(randLength);

    fprintf(inFile, "%s", randStr.c_str());
    fclose(inFile);


    FILE* outFile = fopen(outFileName.c_str(), "w");
    if (!outFile) {
        cerr << "Error: Could not open file " << outFileName << " for writing." << endl;
        return;
    }

    string answer = encoder(randStr);
  
    fprintf(outFile, "%s", answer.c_str());
    fclose(outFile);
}

int main() {
    srand(time(nullptr));

    int n; cin >> n;
    for(int i=1; i<=n; i++){
        string inFileName = "input" + to_string(i) + ".txt";
        string outFileName = "output" + to_string(i) + ".txt";
        generateTestCase(inFileName, outFileName);
    }

    return 0;
}
