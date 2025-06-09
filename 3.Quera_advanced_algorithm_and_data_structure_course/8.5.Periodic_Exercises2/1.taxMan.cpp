#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

bool isForbidden(string s) {
    return s == "110" || s == "101" || s == "111" || s == "011";
}

// Convert number to last 3 digit string
string toStr(int x){
    string str = "";
    for (int i=2; i>=0; i--)
        str += ((x >> i) & 1) + '0';
    return str;
};

int main() {
    int n; cin >> n;

    // Number of valid binary strings with length i and state s of DFA(8 state for 3 last digits)
    vector<vector<long long>> dp(n + 1, vector<long long>(8, 0));

    dp[0][0] = 1;

    for (int i=0; i<n; i++) {
        for (int s=0; s<8; s++) {
            string curr = toStr(s);
            if (isForbidden(curr)) 
                continue;

            // Add 0
            int ns0 = ((s << 1) & 7);
            dp[i + 1][ns0] = (dp[i + 1][ns0] + dp[i][s]) % MOD;

            // Add 1
            int ns1 = ((s << 1) | 1) & 7;
            dp[i + 1][ns1] = (dp[i + 1][ns1] + dp[i][s]) % MOD;
        }
    }

    long long result = 0;
    for (int s=0; s<8; s++) {
        string curr = toStr(s);
        if (!isForbidden(curr)) {
            result = (result + dp[n][s]) % MOD;
        }
    }

    cout << result << endl;
    
    return 0;
}
