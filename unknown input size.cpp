//https://quera.org/course/assignments/64951/problems/220535
    //struggling with opening file and storing data:
    // first thing that came to my mind was using array simply but for that we need to know size of array(we can give a max user size like 500 or read the file twice, first iterating line by line and count number of users, then declare array with size of number of users and after that iterating on file for storing data in that array).
    // another way is that we don't store data at all and iterate on file line by line and do our work but this isn't good in our case that we need to do several works on data.
    // a good way is using vector but we can't beacause of our syllabus
    // another aproach is that we declare a pointer and in reading file after each line realloc array with plus one size but this can't be done cause we use string in our project
    // the way i'm implementing is vectors.
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> numbers;
    int n;
    while(cin >> n)
    {
        numbers.push_back(n);
    }


    for(int i=0; i<numbers.size(); i++)
    {
        cout << numbers[i] << endl;
    }
    return 0;
}