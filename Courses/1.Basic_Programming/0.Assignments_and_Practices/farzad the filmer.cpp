#include <iostream>
#include <cstring>

using namespace std;

void correctForm(char* movie)
{
    char correct[1000] = {'\0'};
    //converting the first character to upper case using ascci codes;
    //managing the first character
    if(movie[0] >= 97 && movie[0] <= 122)
        correct[0] = movie[0]-32;
    else
    {
        correct[0] = movie[0];
    }

    //iterating on characters for making lowercase;
    int l = strlen(movie);
    for (int k = 1; k < l; k++)
    {
        //checking if character is uppercase and make it lowercase and add anything else itself;
        if(movie[k] >= 65 && movie[k] <= 90)
        {
            correct[k] = movie[k] +32;
        }else
        {
            correct[k] = movie[k];
        }
    }
    cout << correct << " ";

}

int main() {
    char m[2];
    cin.getline(m, 2);
    int n = stoi(m);

    char movies[n][1000];
    for(int i=0; i<n; i++)
    {
        cin.getline(movies[i], 1000, '\n');
    }

    //iterating on every string given and make changes;
    for(int j=0; j<n; j++)
    {
        //split film name;
        int l = strlen(movies[j]);

        int z = 0;

        while(z <= l)
        {
            char tmp[100] = {'\0'};
            int e = 0;
            while (movies[j][z] != ' ')
            {
                tmp[e] = movies[j][z];
                z++;
                e++;
                if(z == l)
                    break;
            }

            correctForm(tmp);
            z++;
        }
        cout << endl;

    }


    return 0;
}
