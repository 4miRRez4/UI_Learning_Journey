// https://quera.org/contest/assignments/67462/problems/233362
#include <bits/stdc++.h>

using namespace std;

#define debug(x) cout << #x << ": " << x << endl;

int main()
{
    string str;
    cin >> str;
    int alpha[26] = {};
    for (int i = 0; i < str.size(); i++)
    {
        alpha[str[i] - 'A']++;
    }

    int c = 0;

    string word = "EYA";
    int mn1 = 10000000;
    char ind = 0;
    for (int i = 0; i < word.size(); i++)
    {
        if (alpha[word[i] - 'A'] < mn1)
        {
            mn1 = alpha[word[i] - 'A'];
        }
    }
    int mn2 = 100000;
    word = "MLHV";
    for (int i = 0; i < word.size(); i++)
    {
        if (alpha[word[i] - 'A'] < mn2)
        {
            mn2 = alpha[word[i] - 'A'];
        }
    }

    if ((mn1 / 2) < mn2)
    {
        cout << mn1 / 2 << endl;
    }
    else
        cout << mn2 << endl;
    // if (ind == 'E' || ind == 'Y' || ind == 'A')
    //     cout << mn / 2;
    // else
    //     cout << mn;

    return 0;
}