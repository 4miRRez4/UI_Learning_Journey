#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string word; cin >> word;
    sort(word.begin(), word.end());

    int oddCounter = 0;
    char oddChar = ' ';
    vector<char> letters;
    for(int i=0; i<word.length(); i++)
    {
        auto isThere = find(letters.begin(), letters.end(), word[i]);
        if(isThere == letters.end())
        {
            letters.push_back(word[i]);
            if(count(word.begin(), word.end(), word[i]) %2 != 0)
            {
                oddCounter++;
                oddChar = word[i];
            }
            if(oddCounter > 1)
            {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
        }
    }

    string half="";
    for(int i=0; i<letters.size(); i++)
    {
        int charHalf = (count(word.begin(), word.end(), letters[i])/2);
        for(int j=0; j<charHalf; j++)
           half += letters[i];
    }
    cout <<  half ;
    if(oddCounter == 1)
        cout << oddChar;
    reverse(half.begin(), half.end());
    cout <<  half;




    return 0;
}