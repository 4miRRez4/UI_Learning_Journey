//finding out if a word is palindrome
#include <iostream>
using namespace std;

int len(string word)
{
    int l=0;
    while(word[l])
        l++;
    return l;
}

bool isPalindrome(string word)
{
    string reversed = "";
    int l = len(word);
    for(int i=l-1; i>=0; i--)
        reversed += word[i];
    
    if(word == reversed)
        return true;
    else
        return false;
}

void makeLower(string& word)
{
    int i=0;
    while(word[i])
    {
        if(word[i] >= 'A' && word[i] <= 'Z')
            word[i] = word[i] - 32;
        i++;
    }
}

bool isAlphabet(char suspect)
{
    if(suspect >='a' && suspect <='z')
        return true;
    else
        return false;
}

bool isPalindrome2(string word, int s, int e, int l)
{
    //in this one, non alphabetical word doesn't matter and it isn't case sensitive. it's recursive.
    //base case: checking if we have reached to middle of the word;
    if(s == (l-1)/2 +1)
        return true;
    
    //checking if current character is alphabetical
    if(!isAlphabet(word[s]))
        s++;
    if(!isAlphabet(word[e]))
        e--;

    //comparing characters
    if(word[s] != word[e])
        return false;
    else
        return isPalindrome2(word, s+1, e-1, l);//if two characters are ok, go to compare middler characters;
}

int main()
{
    string word; cin >> word;
    cout << isPalindrome(word) << endl;

    makeLower(word);
    cout << isPalindrome2(word, 0, len(word)-1, len(word));

    return 0;
}