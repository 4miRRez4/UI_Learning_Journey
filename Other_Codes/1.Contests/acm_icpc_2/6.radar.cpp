//https://quera.org/contest/assignments/67462/problems/233377
#include <bits/stdc++.h>

using namespace std;

float comp(pair<float, float> a, pair<float, float> b)
{
    return a.second < b.second;
}

int main()
{
    int t;
    cin >> t;

    int result[t];

    for (int loop = 0; loop < t; ++loop)
    {
        int n, d;
        cin >> n >> d;
        vector<pair<float, float>> dots;

        bool flag = true;

        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            if (y > d)
            {
                flag = false;
            }
            else
            {
                float delta = sqrt(d * d - y * y);
                dots.push_back({x - delta, x + delta});
            }
        }

        if (!flag)
        {
            result[loop] = -1;
            continue;
        }

        sort(dots.begin(), dots.end(), comp);

        int radar = 0;
        float last = -1000000000;

        for (pair<float, float> baze : dots)
        {
            if (last < baze.first)
            {
                last = baze.second;
                radar++;
            }
        }

        result[loop] = radar;
    }

    for (int i = 0; i < t; i++)
    {
        cout << "Case " << (i + 1) << ": " << result[i] << endl;
    }

    return 0;
}
