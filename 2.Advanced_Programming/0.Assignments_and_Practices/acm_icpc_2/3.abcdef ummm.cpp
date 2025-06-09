//https://quera.org/contest/assignments/67462/problems/233365
#include <bits/stdc++.h>
using namespace std;

int t, N, sorat, makhraj, counter, i, k;
char nums[11], decimal[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
bool is_okay;

int check()
{
    string sorat_str = to_string(sorat);
    string makhraj_str = to_string(makhraj);

    while (sorat_str.size() < 5)
    {
        sorat_str = "0" + sorat_str;
    }
    while (makhraj_str.size() < 5)
    {
        makhraj_str = "0" + makhraj_str;
    }

    string combined = sorat_str + makhraj_str;

    copy(combined.begin(), combined.end(), nums);
    nums[10] = '\0';
    for (i = 0; i < 10; i++)
    {
        counter = 0;
        for (k = 0; k < 10; k++)
        {
            if (nums[k] == decimal[i])
                counter++;
        }

        if (counter != 1)
            return 0;
    }

    return 1;
}

int main()
{
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> N;
        is_okay = false;

        makhraj = 1234;
        while (makhraj <= 98765)
        {
            sorat = N * makhraj;
            if (sorat > 98765)
                break;
            if (check())
            {
                for (int i = 0; i < 5 - (to_string(sorat).size()); i++)
                {
                    cout << "0";
                }
                cout << sorat << " / ";
                for (int i = 0; i < 5 - (to_string(makhraj).size()); i++)
                {
                    cout << "0";
                }
                cout << makhraj << " = ";
                cout << N << endl;
                is_okay = true;
            }
            makhraj++;
        }

        if (!is_okay)
            cout << "There are no solutions for " << N << "." << endl;
    }

    return 0;
};