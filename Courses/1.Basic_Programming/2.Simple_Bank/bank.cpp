#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

struct userData{
    string fullName;
    int accountNumber;
    string city;
    long long phoneNumber;
    long long wallet =0;
};

struct transaction{
    string date;
    int accountNumber;
    int amount;
    string type;
};

void invalidInput(int borderCode, int textCode, int frameLen);

void clearTerminal() {
    cout << "\033[2J\033[H"; // ANSI escape codes to clear the screen
    //system("clear || cls");
}

void changeTextColor(int colorCode) {
// [0;31m	Red
// [1;31m	Bold Red
// [0;32m	Green
// [1;32m	Bold Green
// [0;33m	Yellow
// [01;33m	Bold Yellow
// [0;34m	Blue
// [1;34m	Bold Blue
// [0;35m	Magenta
// [1;35m	Bold Magenta
// [0;36m	Cyan
// [1;36m	Bold Cyan
    cout << "\033[1;" << colorCode << "m";
}

void resetTextColor() {
    cout << "\033[0m";
}

int strLen(string str)
{
    int i =0;
    int l =0;
    while(str[i])
    {
        i++;
        l++;
    }
    return l;
}

void printNtime(char character, int n)
{
    for(int i=0; i<n; i++)
        cout << character;
}

void printSymmetry(string out, int borderCode, int textCode, int frameLen)
{
    int length = strLen(out);

    changeTextColor(borderCode);
    cout << "$";
    changeTextColor(textCode);
    printNtime(' ', (frameLen-length-2)/2);
    cout << out;
    printNtime(' ', (frameLen-length-2)/2);
    if(length%2 != 0) cout << " ";
    changeTextColor(borderCode);
    cout<< "$" << endl;

}

void printOptions(int borderCode, int textCode, int frameLen)
{
    changeTextColor(borderCode);
    printNtime('$', frameLen); cout << endl;
    printSymmetry("press:  1->PrintTransactions  2->SearchTransactions ", borderCode, textCode, frameLen);
    printSymmetry("        3->PrintOutlierData   4->CreatingAccount    ", borderCode, textCode, frameLen);
    printSymmetry("        5->GenerateReport    6->Wallet      7->Exit ", borderCode, textCode, frameLen);
    printNtime('$', frameLen); cout << endl;
    printSymmetry("Please press a key", borderCode, textCode, frameLen);
    printNtime('$', frameLen); cout << endl;
}

int stringToInt(string str)
{
    int out=0;
    int i=0;
    int p=1;
    while(str[i])
    {
        int digit = str[i]-'0';
        out = out*10 + digit;
        i++;
    }
    return out;
}

long long stringToLong(string str)
{
    long long out=0;
    int i=0;
    int p=1;
    while(str[i])
    {
        int digit = str[i]-'0';
        out = out*10 + digit;
        i++;
    }
    return out;
}

string intToString(int num)
{
    string rev = "";
    while(num != 0)
    {
        int digit = num%10;
        rev += digit+48;
        num = (num-digit)/10;
    }
    string out = "";
    for(int i=strLen(rev)-1; i>=0; i--)
    {
        out += rev[i];
    }
    return out;
}

// using realloc(it has problem with string and)
// transaction* openingFileRealloc(string fileName)
// {
//     //using realloc and char[];
//     //opening the file
//     ifstream inputFile(fileName);
//     if(!inputFile.is_open())
//     {
//         cout << "Error opening the file!!!";
//     }
//     transaction* transactionArrayT = nullptr; //a pointer with type of struct transaction to a space in memory as start of array;
//     int transactionCounter=0; //number of transactions that have been read from file;
//     //reading file line by line and after reading each line updating allocated memory with larger size
//     string line;
//     while(getline(inputFile, line))
//     {
//         // allocating memory with size of old allocated data size plus one
//         transaction* transactionArrayTmp = (transaction*) realloc(transactionArrayT, (transactionCounter+1) * sizeof(transaction));
//         transactionArrayT = transactionArrayTmp;//test
//         //processing the current line and seperating its data with ','
//         char seperated[4][30] = {};
//         int charInd = 0;
//         int seperatedInd=0;
//         int i=0;
//         while(line[charInd] != '\0')//iterating on line character by character
//         {
//             if(line[charInd] != ',')
//             {
//                 seperated[seperatedInd][i] = line[charInd];
//                 i++;
//             }else
//             {
//                 seperatedInd++;
//                 i=0;
//             }
//             charInd++;
//         }
//         //updating transaction counter
//         strcpy(transactionArrayT[transactionCounter].date, seperated[0]);
//         strcpy(transactionArrayT[transactionCounter].accountNumber, seperated[1]);
//         strcpy(transactionArrayT[transactionCounter].amount, seperated[2]);
//         strcpy(transactionArrayT[transactionCounter].type, seperated[3]);
//         transactionCounter++;
//     }
//     return transactionArrayT;
// }

userData* storingUserData(int& userCounter)
{
    //opening the file
    ifstream inputUsers("users.csv");
    if(!inputUsers.is_open())
    {
        cout << "Error opening the file!!!";
        return nullptr;
    }

    userData* userDataArray = nullptr;//a pointer with type of struct userData to a space in memory as start of array;
    //userCounter -> numbers of users that have been read from file;

    //reading file line by line and after reading each line updating allocated memory with larger size
    string line;
    bool isFirstLine = true;
    while(getline(inputUsers, line))
    {
        if(isFirstLine) //managing first line of data
        {   
            isFirstLine = false;
            continue;
        }

        // allocating memory with size of old allocated data size plus one
        userData* userDataArrayTmp= new userData[userCounter+1];

        // checking if there is problem in allocating memory
        if (userDataArrayTmp == nullptr) {
            cout << "Memory allocation failed." << endl;
            delete [] userDataArrayTmp;  // Clean up the previously allocated memory
            return nullptr;
        }

        // copy existing elements to the new array
        for (int i = 0; i < userCounter; ++i) {
            userDataArrayTmp[i] = userDataArray[i];
        }

        // processing the current line and seperating its data with ','
        string seperatedLine[5]={""};
        int seperatedLineInd=0; 
        int charInd=0; 
        while(line[charInd] != '\0')
        {
            if(line[charInd] != ',')
            {
                seperatedLine[seperatedLineInd] += line[charInd];
            }else
                seperatedLineInd++;
            
            charInd++;
        }

        //adding current line datas
        userDataArrayTmp[userCounter].fullName = seperatedLine[0];
        userDataArrayTmp[userCounter].accountNumber = stringToInt(seperatedLine[1]);
        userDataArrayTmp[userCounter].city = seperatedLine[2];
        userDataArrayTmp[userCounter].phoneNumber = stringToLong(seperatedLine[3]);
        userDataArrayTmp[userCounter].wallet = stringToLong(seperatedLine[4]);

        // updating the pointer to new allocated memory
        delete[] userDataArray;
        userDataArray = userDataArrayTmp;
 
        userCounter++;
    }
    return userDataArray;
}

transaction* storingTransaction(int& transactionCounter)
{
    //opening the file
    ifstream inputFile("transaction.csv");
    if(!inputFile.is_open())
    {
        cout << "Error opening the file!!!";
        return nullptr;
    }

    transaction* transactionArray = nullptr;//a pointer with type of struct userData to a space in memory as start of array;
    //transactionCounter -> numbers of users that have been read from file;

    //reading file line by line and after reading each line updating allocated memory with larger size
    string line;
    bool isFirstLine = true;
    while(getline(inputFile, line))
    {
        if(isFirstLine)//skiping first line of data
        {
            isFirstLine=false;
            continue;
        }

        // allocating memory with size of old allocated data size plus one
        transaction* transactionArrayTmp= new transaction[transactionCounter+1];

        // checking if there is problem in allocating memory
        if (transactionArrayTmp == nullptr) {
            cout << "Memory allocation failed." << endl;
            delete[] transactionArrayTmp;  // Clean up the previously allocated memory
            return nullptr;
        }

        // copy existing elements to the new array
        for (int i = 0; i < transactionCounter; ++i) {
            transactionArrayTmp[i] = transactionArray[i];
        }

        // processing the current line and seperating its data with ','
        string seperatedLine[4]={""};
        int seperatedLineInd=0; 
        int charInd=0; 
        while(line[charInd] != '\0')
        {
            if(line[charInd] != ',')
            {
                seperatedLine[seperatedLineInd] += line[charInd];
            }else
                seperatedLineInd++;
            
            charInd++;
        }

        //adding current line datas
        transactionArrayTmp[transactionCounter].date = seperatedLine[0];
        transactionArrayTmp[transactionCounter].accountNumber = stringToInt(seperatedLine[1]);
        transactionArrayTmp[transactionCounter].amount = stringToInt(seperatedLine[2]);
        transactionArrayTmp[transactionCounter].type = seperatedLine[3];

        // updating the pointer to new allocated memory
        delete[] transactionArray;
        transactionArray = transactionArrayTmp;
 
        transactionCounter++;
    }
    return transactionArray;
}

void sortByAccountNumT(transaction* transactionArray, int transactionCounter)
{
    //insertion sort 
    int i,j;
    for(i=1; i<transactionCounter; i++)
    {
        transaction selected = transactionArray[i];
        for(j=i-1; j>=0; j--)
        {
            if(transactionArray[j].accountNumber > selected.accountNumber)
            {
                transactionArray[j+1] = transactionArray[j];
            }else
            {
                break;
            }
        }
        transactionArray[j+1] = selected;
    }
}

void sortByAccountNumU(userData* userDataArray, int userCounter)
{
    //insertion sort 
    int i,j;
    for(i=1; i<userCounter; i++)
    {
        userData selected = userDataArray[i];
        for(j=i-1; j>=0; j--)
        {
            if(userDataArray[j].accountNumber > selected.accountNumber)
            {
                userDataArray[j+1] = userDataArray[j];
            }else
            {
                break;
            }
        }
        userDataArray[j+1] = selected;
    }
}

// int searchTimeInd(transaction* transactionArray, string specificTime)
// {
//     //using binary search to find first index of specific year and month
//     int first=0,last=transactionLen(transactionArray)-1, mid;
//     while(first<=last)
//     {
//         mid=(first+last) /2;
//         if(transactionArray[mid].date.substr(0,7) == specificTime)
//         {
//             while(transactionArray[mid].date.substr(0,7) == specificTime)
//             {
//                 mid--;
//             }
//             return mid+1;
//         }else if(transactionArray[mid].date.substr(0,7) < specificTime)
//         {
//             first = mid+1;
//         }else
//         {
//             last = mid-1;
//         }
//     }
//     return -1;
// }

int searchTimeInd(transaction* transactionArray, string specificYear, int transactionCounter)
{
    //using binary search to find first index of specific year
    int first=0,last=transactionCounter, mid;
    while(first<=last)
    {
        mid=(first+last) /2;
        if(transactionArray[mid].date.substr(0,4) == specificYear)
        {
            while(transactionArray[mid].date.substr(0,4) == specificYear)
            {
                mid--;
            }
            return mid+1;
        }else if(transactionArray[mid].date.substr(0,4) < specificYear)
        {
            first = mid+1;
        }else
        {
            last = mid-1;
        }
    }
    return -1;
    
}

int searchAccountInd(transaction* transactionArray, int accountNumber, int transactionCounter)
{
    //using binary search to find first index of specific year
    int first=0,last=transactionCounter, mid;
    while(first<=last)
    {
        mid=(first+last) /2;
        if(transactionArray[mid].accountNumber == accountNumber)
        {
            while(transactionArray[mid].accountNumber == accountNumber)
            {
                mid--;
            }
            return mid+1;
        }else if(transactionArray[mid].accountNumber < accountNumber)
        {
            first = mid+1;
        }else
        {
            last = mid-1;
        }
    }
    return -1;
    
}

userData searchAccountIndU(userData* userDataArray, int accountNumber, int userCounter)
{
    //using binary search to find first index of specific year
    int first=0,last=userCounter-1, mid;
    while(first<=last)
    {
        mid=(first+last) /2;
        if(userDataArray[mid].accountNumber == accountNumber)
        {
            return userDataArray[mid];
        }else if(userDataArray[mid].accountNumber < accountNumber)
        {
            first = mid+1;
        }else
        {
            last = mid-1;
        }
    }
    return userDataArray[0];
}

string findFullName(userData* userDataArray, int userCounter, int accountNumber)
{
    //using binary search to find full name of specific account number
    int first=0,last=userCounter, mid;
    while(first<=last)
    {
        mid=(first+last) /2;
        if(userDataArray[mid].accountNumber == accountNumber)
        {
            return userDataArray[mid].fullName;
        }
        else if(userDataArray[mid].accountNumber < accountNumber)
        {
            first = mid+1;
        }
        else
        {
            last = mid-1;
        }
    }
    return "n";
}

int findingMedian(transaction* specificAccount,int first, int last)
{
    int size = last - first +1;
    int mid = size/2;
    return size%2 == 0 ? specificAccount[mid].amount+specificAccount[mid-1].amount/2 : specificAccount[mid].amount;
}

void writingOnTransactionFile(transaction* transactionArray, int transactionCounter)
{
    //opening file
    ofstream outFile("transaction.csv");

    //checking problem opening file
    if(!outFile.is_open())
    {
        cout << "Error opening the file!!!";
    }

    //writing line 1
    outFile << "Date,AccountNumber,Amount,Type" << endl;

    //iterating on array and writing it in file
    for(int i=0; i<transactionCounter; i++)
    {
        outFile << transactionArray[i].date << "," << transactionArray[i].accountNumber << ",";
        outFile << transactionArray[i].amount << "," << transactionArray[i].type << endl;
    }
}

void writingOnUsersFile(userData* userDataArray, int userCounter)
{
    //opening file
    ofstream outFile("users.csv");

    //checking problem opening file
    if(!outFile.is_open())
    {
        cout << "Error opening the file!!!";
    }

    //writing line 1
    outFile << "FullName,AccountNumber,City,PhoneNumber,Wallet" << endl;

    //iterating on array and writing it in file
    for(int i=0; i<userCounter; i++)
    {
        outFile << userDataArray[i].fullName << "," << userDataArray[i].accountNumber << ",";
        outFile << userDataArray[i].city << "," << userDataArray[i].phoneNumber << ",";
        outFile << userDataArray[i].wallet << endl;
    }
}

void invalidInput(int borderCode, int textCode, int frameLen)
{
    printSymmetry("Invalid input! please try again.", borderCode, textCode, frameLen);
    printNtime('$', frameLen);

    // Adding a delay
    this_thread::sleep_for(chrono::seconds(1));
    clearTerminal();
}

void z_score_outliers(transaction* specificAccount, int n)
{
    //using z-score aproach:
    //calculating mean:
    int sum=0;
    for(int i=0; i<n; i++)
    {
        sum += specificAccount[i].amount;
    }
    int mean = sum/n;

    //calculating standar deriviation
    int squaredDiff =0;
    for(int i=0; i<n; i++)
    {
        squaredDiff += (specificAccount[i].amount - mean) * (specificAccount[i].amount - mean);
    }
    double variance = squaredDiff/n;
    double stdDer = sqrt(variance);

    
    float z_score = 0;
    for(int i=0; i<n; i++)
    {
        z_score = (specificAccount[i].amount - mean) / stdDer;
        if(z_score > 1.5)
        {
            string line = specificAccount[i].date + " - " + intToString(specificAccount[i].accountNumber) + " - ";
            line += intToString(specificAccount[i].amount) + " - " + specificAccount[i].type;

            cout << line << endl;
        }
        
    }
}

void IQR_outliers(transaction* specificAccount, int n)
{
    //using IQR approach:
    float Q1 = findingMedian(specificAccount, 0, n/2-1);
    float Q3 = findingMedian(specificAccount, n/2, n-1);

    float IQR = Q3-Q1;
    float upperFence = Q3 + (1.5 * IQR);
    
    for(int i=0; i<n; i++)
    {
        if(specificAccount[i].amount > upperFence)
        {
            string line = specificAccount[i].date + " - " + intToString(specificAccount[i].accountNumber) + " - ";
            line += intToString(specificAccount[i].amount) + " - " + specificAccount[i].type;

            cout << line << endl;
        }
    }
}

int main()
{
    //struggling with opening file and storing data:
    // first thing that came to my mind was using array simply but for that we need to know size of array(we can give a max user size like 500 or read the file twice, first iterating line by line and count number of users, then declare array with size of number of users and after that iterating on file for storing data in that array).
    // another way is that we don't store data at all and iterate on file line by line and do our work but this isn't good in our case that we need to do several works on data.
    // a good way is using vector but we can't beacause of our syllabus
    // another aproach is that we declare a pointer and in reading file after each line realloc array with plus one size but this can't be done cause we use string in our project
    // the way i'm implementing is previous logic with using new.
    
    //data road: file->dynamic array->working on array->file

    //loading data and storing them
    int userCounter =0;
    userData* userDataArray = storingUserData(userCounter);
    int transactionCounter =0;
    transaction* transactionArray = storingTransaction(transactionCounter);

    int frameLen = 70, borderCode=35, textCode=36;//default frame

    while(true)
    {
        clearTerminal();
        printOptions(borderCode, textCode, frameLen);
        
        int key; cin >> key;
        switch (key)
        {
            case 1://print transaction
            {
                //sorting transaction based on account number;
                sortByAccountNumT(transactionArray, transactionCounter);
                sortByAccountNumU(userDataArray, userCounter);
            
                int accNum; 
                cout << "Please enter your Account Number: ";
                cin >> accNum;

                string name = findFullName(userDataArray, userCounter, accNum);//searching name for this account
                if(name == "n")// checking if is there a name for that account
                {
                    cout << accNum;
                    cout << "Fuckfuck";
                    invalidInput(borderCode, textCode, frameLen);
                    break;
                }
                int startInd = searchAccountInd(transactionArray, accNum, transactionCounter);//start index of specific account number

                //printing
                clearTerminal();
                printNtime('$', 42); cout << endl;
                printSymmetry("$ Transactions of " + name +" $", borderCode, textCode, 42);
                printSymmetry(" ", borderCode, textCode, 42);
                printSymmetry("Date - AccountNumber - Amount - Type", borderCode, textCode, 42);
                printSymmetry(" ", borderCode, textCode, 42);
                while(transactionArray[startInd].accountNumber == accNum)
                {
                    string line = transactionArray[startInd].date + " - " + intToString(transactionArray[startInd].accountNumber) + " - ";
                    line += intToString(transactionArray[startInd].amount) + " - " + transactionArray[startInd].type;

                    printSymmetry(line, borderCode, textCode, 42);

                    startInd++;
                    if(startInd >= transactionCounter)
                        break;
                }
                printSymmetry(" ", borderCode, textCode, 42);
                printSymmetry("**HAVE A GOOD DAY**", borderCode, textCode, 42);
                printNtime('$', 42);

                cout << endl << "Enter any key to continue: "<< endl;
                char tmp; cin >> tmp;

                break;
            }
            case 2://search transactions
            {
                clearTerminal();
                sortByAccountNumT(transactionArray, transactionCounter);

                string year;
                cout << "Please enter year: ";
                cin >> year;
                int accNum;
                cout << endl << "Please enter your account number: ";
                cin >> accNum;
                string type;
                cout << endl << "Please enter type: ";
                cin >> type; cout << endl;

                int startInd = searchAccountInd(transactionArray, accNum, transactionCounter);//start index of specific account number
                while(transactionArray[startInd].accountNumber == accNum)
                {
                    if(transactionArray[startInd].date.substr(0,4) == year && transactionArray[startInd].type == "\""+type+"\"")
                    {
                        string line = transactionArray[startInd].date + " - " + intToString(transactionArray[startInd].accountNumber) + " - ";
                        line += intToString(transactionArray[startInd].amount) + " - " + transactionArray[startInd].type;

                        printSymmetry(line, borderCode, textCode, 42);
                    }
                    startInd++;
                    if(startInd >= transactionCounter)
                        break;
                }


                cout << endl << "Enter any key to continue: "<< endl;
                char tmp; cin >> tmp;
                break;
            }
            case 3://spotting outlier data
            {
                clearTerminal();
                //creating a temp array for data of specific user
                sortByAccountNumT(transactionArray, transactionCounter);
                int accNum; 
                cout << "Please enter account number that you wanna check: ";
                cin >> accNum;
                int startInd = searchAccountInd(transactionArray, accNum, transactionCounter);

                int i = startInd;
                int n=0;
                transaction* specificAccount= nullptr;
                while(transactionArray[i].accountNumber == accNum)
                {
                    transaction* specificAccountTmp = new transaction[n+1];
                    for(int j=0; j<n;j++)
                        specificAccountTmp[j] = specificAccount[j];
                    delete[] specificAccount;
                    specificAccount = specificAccountTmp;
                    specificAccount[n] = transactionArray[i];
                    n++;
                    i++;
                }

                //using z_score approach
                // z_score_outliers(specificAccount, n);

                //using IQR approach
                IQR_outliers(specificAccount, n);

                delete[] specificAccount;
                cout << endl << "Enter any key to continue: "<< endl;
                char tmp; cin >> tmp;
                break;
            }
            case 4://opening an account(adding to users file)
            {
                //making space for new user
                userData* tmp = new userData[userCounter+1];
                // checking if there is problem in allocating memory
                if (tmp == nullptr) {
                    cout << "Memory allocation failed." << endl;
                    delete [] tmp;  // Clean up the previously allocated memory
                    return -1;
                }
                //copying existing users to new array
                for(int i=0; i<userCounter; i++)
                    tmp[i] = userDataArray[i];
                //adding new user
                cout << "Please enter your name: ";
                cin >> tmp[userCounter].fullName;
                cout << endl <<"Please enter your account number: ";
                cin >> tmp[userCounter].accountNumber;
                cout << endl <<"Please enter your city: ";
                cin >> tmp[userCounter].city;
                cout << endl <<"Please enter your phone number: ";
                cin >> tmp[userCounter].phoneNumber;
                cout << endl<<"Please enter your wallet: ";
                cin >> tmp[userCounter].wallet;
                cout << endl;
                // updating the pointer to new allocated memory
                delete[] userDataArray;
                userDataArray = tmp;
            
                userCounter++;

                break;
            }
            case 5://saving data for specific user with specific type in file
            {
                //creating a temp array for data of specific user
                sortByAccountNumT(transactionArray, transactionCounter);
                int accNum;
                cout << "Please enter account number: ";
                cin >> accNum;
                string type;
                cout << "Please enter type: ";
                cin >> type;
                int startInd = searchAccountInd(transactionArray, accNum, transactionCounter);

                int i = startInd;
                int n=0;
                transaction* specificAccount= nullptr;
                while(transactionArray[i].accountNumber == accNum)
                {
                    transaction* specificAccountTmp = new transaction[n+1];
                    for(int j=0; j<n;j++)
                        specificAccountTmp[j] = specificAccount[j];
                    delete[] specificAccount;
                    specificAccount = specificAccountTmp;
                    specificAccount[n] = transactionArray[i];
                    n++;
                    i++;
                }

                //opening file 
                ofstream outFile(intToString(accNum) + ".csv");

                // checking if the file is opened successfully
                if (!outFile.is_open()) {
                    cout << "Error opening file!" << endl;
                    return 1;
                }

                //iterating throgh data of specific user and check if it is wanted type
                for(int j=0; j<n; j++)
                {
                    if(specificAccount[j].type == "\""+type+"\"")
                    {
                        //saving to file
                        outFile << specificAccount[j].date << "," << specificAccount[j].accountNumber << ",";
                        outFile << specificAccount[j].amount << "," << specificAccount[j].type << endl;
                    }
    
                }

                delete[] specificAccount;
                break;
            }
            case 6://watching wallet
            {
                clearTerminal();
                sortByAccountNumU(userDataArray, userCounter);
                cout << "please enter your account numbers: ";
                int accNum; cin >> accNum;
                userData user = searchAccountIndU(userDataArray, accNum, userCounter);
                cout << "your wallet is: " << user.wallet;

                cout << endl << "Enter any key to continue: "<< endl;
                char tmp; cin >> tmp;
                break;
            }
            case 7://exiting the program
            {
                //updating file
                writingOnTransactionFile(transactionArray, transactionCounter);
                writingOnUsersFile(userDataArray, userCounter);

                // cleaning up previously allocated memory
                delete[] userDataArray;
                delete[] transactionArray;

                clearTerminal();
                printNtime('$', frameLen); cout << endl;
                printSymmetry("**HAVE A GOOD DAY**", borderCode, textCode, frameLen);
                printNtime('$', frameLen); cout << endl;

                return 0;
            }
            default:
            {
                invalidInput(borderCode, textCode, frameLen);
            }
        }
    }

}