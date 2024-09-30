#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int t; cin >> t;

    for(int i=0; i<t; i++)//numbers of scenarios;
    {
        int n,k; cin >> n >> k;
        char str[n]; cin >> str;

        int chocolate=0;
        //counting chocolates in present situation;
        for(int j=0; j<n; j++)//iterating on characters;
        {
            char selected = str[j];
            if(selected == 0) continue;

            for(int k=j+1; k<n; k++)//iterating on characters after selected one;
            {
                if((str[k] == selected+32) || (str[k] == selected-32))//checking if character after selected in upper case or lower case of selected one;
                {
                    chocolate++;
                    str[k]=0;
                    str[j]=0;
                    break;
                }

            }

        }

        //making changes for earning chocolate;
        for(int i=0; i<n; i++)//iterating on leftovers of character
            {
                if(k==0) break;
                char selected = str[i];
                if(selected == 0) continue;

                for(int j=i+1; j<n; j++)//iterating on character after selected one;
                {
                    if(selected == str[j])
                    {
                        chocolate++;
                        str[i]=0;
                        str[j]=0;
                        k--;
                        break;
                    }
                }
            }


        cout << chocolate << endl;
    }


    return 0;
}
