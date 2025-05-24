#include <iostream>
#include <vector>
using namespace std;

int countPermutations(int k, int n, vector<int>& p, vector<bool>& used, int inv) {
    if (p.size() == n) {
        return inv == k ? 1 : 0;
    }

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            int newInv = inv;

            for (int j = 0; j < p.size(); j++) 
                if (p[j] > i) 
                    newInv++;
            
            //Bound
            if (newInv > k) 
                continue; 

            used[i] = true;
            p.push_back(i);
            count += countPermutations(k, n, p, used, newInv);
            p.pop_back();
            used[i] = false;
        }
    }
    return count;
}

int main() {
    int n, k; cin >> n >> k;

    vector<int> p;
    vector<bool> used(n + 1, false);
    cout << countPermutations(k, n, p, used, 0) << endl;

    return 0;
}
