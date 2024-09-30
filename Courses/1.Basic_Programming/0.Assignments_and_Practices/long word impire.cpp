#include <iostream>

using namespace std;

int length(char* p)
{
    //calculating length of the given string;
    int c=0;
    while(*p !='\0')
    {
        c++;
        p++;
    }
    return c;

}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char word[100];
        cin >> word;

        int l = length(word);

        if(l>10)
        {
            //printing first character;
            cout << word[0] << l-2 << word[l-1] << endl;
        }else
        {
            cout << word << endl;
        }

    }










//    char out[n][100];
//    for(int i=0; i<n; i++)
//    {
//        char word[100];
//        fgets(word, 100, stdin);
//        int l = length(word)-1; //this can be done also by strlen function; //-1 because fgets gets \n too;
//
//
//        if(l>10)
//        {
//            //adding the first part of output format;
//            out[i][0] = word[0];
//
//            //adding the second part of output format;
//            int m = l-2;
//            int z = 0;
//            char tmp[50];
//            while(m!=0)
//            {
//                tmp[z] = m%10+'0';
//                m = (m)/10;
//                z++;
//            }
//            for(int b=0; b<z; b++)
//            {
//                out[i][b+1] = tmp[z-1-b];
//            }
//
//            //adding the third part;
//            out[i][z+1] = word[l-1];
//            out[i][z + 2] = '\n';
//            out[i][z + 3] = '\0';
//
//
//        }else
//        {
//            strcpy(out[i],word);
//        }
//
//    }
//
//    for(int k=0; k<c; k++)
//        cout << out[k];

    return 0;
}
