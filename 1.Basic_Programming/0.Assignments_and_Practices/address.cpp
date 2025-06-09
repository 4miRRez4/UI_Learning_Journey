#include <iostream>
using namespace std;

int distance(int s, int e, int size)
{
    //calculating number of elements between two point of array including start and end;
    int out = ((e-s)/size) +1;
    return out;
}

int main() {
    char str[6];
    cin >> str;

    int start;
    cin >> start;
    int end;
    cin >> end;

    int size = 0;
    switch (str[0]) {
        case 'i':
            size = 4;
            break;
        case 'c':
            size = 1;
            break;
        case 'f':
            size = 4;
            break;
        case 'd':
            size = 8;
            break;
    }//this part can be written by if and else and using strcmp(or writing down this function using for loop) but I wrote it with switch case cause its cooler;
//    if(strcmp(str,"int") == 0)
//    {
//        size = 4;
//    }
//    else if(strcmp(str,"char") == 0)
//    {
//        size = 1;
//    }
//    else if(strcmp(str,"float") == 0)
//    {
//        size = 4;
//    }
//    else if(strcmp(str,"double") == 0)
//    {
//        size = 8;
//    }
    
    cout << distance(start, end, size);



    return 0;
}
