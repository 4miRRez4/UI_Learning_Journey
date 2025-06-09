#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i=0; i<n; i++) 
        cin >> a[i];

    // dp[i][s] = min cost to reach area s using first i tiles
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        int old_side = a[i - 1];
        for (int b = 0; b <= 100; ++b) {
            int area = b * b;
            int cost = (old_side - b) * (old_side - b);
            for (int s = 0; s + area <= m; ++s) {
                if (dp[i - 1][s] != INF) {
                    dp[i][s + area] = min(dp[i][s + area], dp[i - 1][s] + cost);
                }
            }
        }
    }

    int ans = dp[n][m];
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}
