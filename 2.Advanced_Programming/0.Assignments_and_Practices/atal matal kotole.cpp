//n people are sitting around one table and playing atal matal totole. game starts with player 0, and rounds k by k. we wunna know how many rounds we must play to get back to player 0 again;
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, k;
    while(cin >> n >> k)
    {
        int rounds=1;
        int players[n];
        for(int i=0; i<n; i++)
            players[i] = i;

        vector<int> history;
        int player = players[(0 + k)%n];

        while(player != 0)
        {
            history.push_back(player);
            player = players[(player + k)%n];
            rounds++;
        }

        cout << rounds << "=>";
        for(int i=0; i<history.size();i++)
        {
            cout << history[i];
        }
    }
    return 0;
}