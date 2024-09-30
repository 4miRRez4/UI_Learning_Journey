#include <iostream>
#include <string.h>
using namespace std;

//void lowered(char** names,int n)
//{
//    for(int i=0; i<n; i++)//iterating on words;
//    {
//        for(int j=0; j<n; j++)//iterating on characters of selected word;
//        {
//            if((names[i][j] >= 'A') && (names[i][j] <= 'Z'))
//                names[i][j] = names[i][j] +32;
//        }
//    }
//}
//void uppered(char** names, int n)
//{
//    for(int i=0; i<n; i++)//iterating on words;
//    {
//        names[i][0] = names[i][0] -32;
//    }
//}


int main() {
    int n;
    cin >> n;

    int l_max =0;
    //getting names from input;
    char **names = new char *[n];
    for (int i = 0; i < n; i++)
    {
        names[i] = new char[100];
        cin >> names[i];

        if(strlen(names[i] ) > l_max){
            l_max = strlen(names[i]);
        }
    }
    //lowered(names,n);
    //for(int i=0; i<n; i++) cout << names[i] << endl;

    //sorting array by end characters using insertion sort;
    int j,k;
    for(j=1; j<n; j++)//iterating on unsorted part
    {
        int l = strlen(names[j]);
        int m = l-1;
        char selectedWord[100] = {};
        strcpy(selectedWord,names[j]);
        char selected = selectedWord[m];

        for(k=j-1; k>=0; k--)// iterating on sorted part;
        {
            int l2 = strlen(names[k]);
            int p = l2-1;
            char selected2 = names[k][p];

            while(selected == selected2)
            {
                selected = selectedWord[--m];
                selected2 = names[k][--p];
            }

            if(selected < selected2) {
                m = l - 1;
                selected = selectedWord[m];
                strcpy(names[k + 1], names[k]); //shifting
            }
            else
            {
                break;
            }
        }
        strcpy(names[k+1],selectedWord); //giving right place to first element of unsorted part in sorted part
    }
    //for(int i=0; i<n; i++) cout << names[i] << endl;

    //calculating scores;
    float score[n];
    for(int z=0; z<n; z++)//iterating on sorted words;
    {
        if(z == n-1){
            score[z] = 18;
            break;
        }
        int l = strlen(names[z]);
        char selectedWord[l];
        strcpy(selectedWord, names[z]);

        int l2 = strlen(names[z+1]);
        char next[l2];
        strcpy(next, names[z+1]);

        int rhymeCounter = 0;
        for(int y=0; y<l; y++)//iterating on characters backward and comparing them;
        {
            if(selectedWord[l-1-y] == next[l2-1-y])
            {
                rhymeCounter++;
            }else
            {
                break;
            }
        }
        int tmp = rhymeCounter*3;
        if(tmp == 9)
        {
            score[z] = tmp-1;
        }else if(tmp == 0)
        {
            score[z] = 0.1;
        }else if(tmp >= 20)
        {
            score[z] = 20;
        }else
        {
            score[z] = tmp;
        }
    }

    //uppered(names,n);

    for(int q=0; q<n; q++)
    {
        int l = strlen(names[q]);
        cout << names[q];
        for(int i =0; i < (l_max-l+1); i++)
        {
            cout << ' ';
        }
        cout << score[q] << endl;
    }

    //deleting allocated memory;
    for(int i=0; i<n; i++)  delete [] names[i];
    delete [] names;


    return 0;
}
