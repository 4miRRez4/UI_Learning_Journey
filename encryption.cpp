/*ehsan mahdavi AP assignment
    -we know that this code is used for decryption:
    
    #include <iostream>
    using namespace std;
    int main(){
        int a[2];
        a[0] = 1634300513;
        a[1] = 110;
        for(char * p = (char *)a ; (*p) !=0 ; p++)
        {
            cout << *p;
        }
    cout<<endl;
    return 0;
    }
    
    -basicly this sticks 4 ascii code of 4 characters together bitwise. (cause int is 4 byte and char is 1 byte)
*/
#include <iostream>
using namespace std;

int main()
{
	string message;
	getline(cin, message);

	//for number of array element that we need for our codes, we can say that cause every 4 character(1 byte) can be stored in 1 int element(4 byte),
	// we need "numberOfCcharacters/4" if number of character isn't 4k, then add one to that. 
	// (we could use vector(resizing our array after each new element needed and in last output the length of that)
	int numberOfElements = message.length()/4;
	if(message.length() % 4 != 0) numberOfElements++;

	//now we iterate through our message and convert each character to its ascii code and place it in our 4 byte.(by using "shift" bitwise operator for changing binary representation of each
	//ascii code place in our 4byte(32 bit) memory for each integer. and then using "or" bitwise operator for combining(placing zeros and ones of new 8 bit of
	//ascii code in each byte of our int 4 byte)
    int encriptedArr[numberOfElements] = {};
    int arrInd = -1;
    for(int c=0; c<message.length(); c++)
    { 
        int asciiCode = (int)message[c];
        if(c%4 == 0) 
            arrInd++;
        encriptedArr[arrInd] = encriptedArr[arrInd] | (asciiCode << 8*(c%4));
    }

    cout << numberOfElements << endl;
    for(int i=0; i<numberOfElements; i++)
        cout << encriptedArr[i] << endl;


    return 0;
}
