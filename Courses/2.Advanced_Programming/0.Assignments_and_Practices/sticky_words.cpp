// https://quera.org/problemset/3434
#include<bits/stdc++.h> 

using namespace std; 

#define debug(x) cout << #x << ":" << x << endl; 

bool custom_compare(const string &word1, const string &word2){
    return word1 + word2 < word2 + word1;
}

int main(){ 
    int n; scanf("%d", &n);
    vector<string> words(n);
    char buffer[25];
    for (int i = 0; i < words.size(); i++)
    {
        scanf("%s", buffer);
        words[i] = buffer;
    }
    
    sort(words.begin(), words.end(), custom_compare);

    for(int i=0; i<n; i++)
        printf("%s", words[i].c_str());
    return 0;
}