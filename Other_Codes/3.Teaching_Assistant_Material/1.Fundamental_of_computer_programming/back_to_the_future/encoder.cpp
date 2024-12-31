#include <iostream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 1000; 
int main()
{
    char message[MAX_SIZE] ={};

    cin.getline(message, MAX_SIZE);
    int message_len = strlen(message);

	int numberOfElements = message_len / 4;
	if(message_len % 4 != 0) numberOfElements++;

    int encriptedArr[numberOfElements] = {};
    int arrInd = -1;
    for(int c=0; c<message_len; c++)
    {
        int asciiCode = message[c];
        if(c%4 == 0) 
            arrInd++;
        encriptedArr[arrInd] = encriptedArr[arrInd] | (asciiCode << 8*(c%4));
    }

    cout << numberOfElements << endl;
    for(int i=0; i<numberOfElements; i++)
        cout << encriptedArr[i] << endl;

    return 0;
}
