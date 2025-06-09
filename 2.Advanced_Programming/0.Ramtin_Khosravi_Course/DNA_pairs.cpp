//assignment 4 of ramting khosravi AP.
//finding maximum pairs of a given dna(a--t and c--g)(circular)
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isPairValid(vector<vector<int>> pairs, string dna, int i, int j)
{
    for(auto pair:pairs)
    {
        if(((i>pair[1] )&& (j>pair[1])) || ((i<pair[0]) && (j<pair[0])) || ((i>pair[0]) && (j<pair[1])) || ((i<pair[0]) && (j>pair[1])))
            continue;
        else
            return false;
    }
    return true;
}

void count_maximum_pairs(vector<vector<int>>& pairs, string dna, int s, int e, char whereNext)
{
    if(s < 0)
        return;
    
    for(int i=s; i<=e; i++)
    {
        char tmp = dna[i];
        for(int j=i+1; j!=e+1; j++)
        {
            if((dna[i] == 'a' && dna[j] =='t') || (dna[i] == 't' && dna[j] =='a') || (dna[i] == 'c' && dna[j] =='g') || (dna[i] == 'g' && dna[j] =='c'))
                if(isPairValid(pairs, dna, i, j))
                {
                        vector<int> a (2);
                        a[0] = i;
                        a[1] = j;
                        pairs.push_back(a);
                        break;
                }
        }       
    }
    if(whereNext == 'r')
        count_maximum_pairs(pairs, dna, s, e+1, 'l');
    else if(whereNext == 'l')
        count_maximum_pairs(pairs, dna, s-1, e, 'r');

}


int main()
{
    string dna; cin >> dna;
    vector<vector<int>> pairs;//[firstIndex, secondIndex],...

    //finding middle of str
    int s,e;
    int l = dna.length();
    if(l%2 == 0)
    {
        s=l/2 -1; e=l/2;
    }
    else
    {
        s=l/2 -1; e=l/2 +1;
    }

    count_maximum_pairs(pairs, dna, s, e, 'r');
    for(auto pair:pairs)
        cout << pair[0] << "," << pair[1] << endl;

    return 0;
}