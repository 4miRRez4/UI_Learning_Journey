#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int n; cin >> n;
    char pattern[n];
    for(int i=0; i<n; i++) cin >> pattern[i];//getting pattern from input;

    char** words = new char*[n];
    for(int i=0; i<n; i++)// getting words from input;
    {
        words[i] = new char[3000];
        cin >> words[i];
    }

    for(int p=0; p<n; p++)// iterating on pattern;
    {
        if(pattern[p] == 0) continue;

        char selectedP = pattern[p];
        char* selectedW = words[p];
        for(int w=p+1; w<n; w++)// iterating on words;
        {
            if(pattern[w] == selectedP)
            {
                if(strcmp(words[w], selectedW) != 0)
                {
                    cout << "NO";
                    return 0;
                }else
                {
                    words[w] = 0;
                    pattern[w] = 0;
                }
            }

        }

    }
    cout << "YES";


    return 0;
}
