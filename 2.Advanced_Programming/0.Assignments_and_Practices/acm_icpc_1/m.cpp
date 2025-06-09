#include <iostream>
#include <string>
using namespace std;

int main()
{
    int days; cin >> days;
    string cards;
    for(int d=0; d<days; d++)
    {
        cin >> cards;
        int operations = 0;
        for(int s=0; s<cards.length(); s++)
        {
            int baze = 0;
            if(cards[s] == '0')
            {
                operations++;
                baze++;
                while(cards[s+baze] == '0')
                {
                    baze++;
                }
            }
            s+=baze;
        }
        cout << operations << endl;
    }

    return 0;
}