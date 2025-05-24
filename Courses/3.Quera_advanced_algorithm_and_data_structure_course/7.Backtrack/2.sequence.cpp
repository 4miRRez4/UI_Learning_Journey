#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e6 + 100;
bool mark[MAX] = {}; 

int count(int n, int curr_seq, vector<vector<int>>& seqs, vector<int>& seq_lens){
    if(curr_seq == n)
        return 1;

    int cnt = 0;
    for(int i = 0; i < seq_lens[curr_seq]; i++){
        int x = seqs[curr_seq][i];
        if(!mark[x]){
            mark[x] = true;
            cnt += count(n, curr_seq+1, seqs, seq_lens);
            mark[x] = false;
        }
    }
    return cnt;
}

int main(){
    int n; cin >> n;
    
    vector<vector<int>> seqs(10, vector<int> (8, -1));
    vector<int> seq_lens(n);
    for(int i = 0; i < n; i++){
        cin >> seq_lens[i];
        for(int j = 0; j < seq_lens[i]; j++)
            cin >> seqs[i][j];
    }

    cout << count(n, 0, seqs, seq_lens) << endl;

    return 0;
}