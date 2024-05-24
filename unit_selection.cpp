//with given prerequisites in what order we can take our unit for this term?
//input: 1 2, 1 3, 3 4, 2 3, 2 4
//output: 1 2 3 4
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int main(){
    int biggest, t; scanf("%d %d", &biggest, &t);
    vector<vector<int>> matris (biggest, vector<int> (biggest,0));
    int numOfPre[biggest] = {};
    
    int i,j;
    for(int k=0; k<t; k++){
        scanf("%d %d", &i, &j);
        matris[i-1][j-1] = 1;
        numOfPre[j-1] ++;
    }

    for(int i=0;i<biggest; i++){
        for(int j=0; j<biggest; j++)
            cout << matris[i][j] << " ";
        cout << endl;
        }
    for(int i=0; i<biggest; i++)
        cout << numOfPre[i] << " ";

    queue<int> q;
    q.push(1);
    while(q.size() != biggest){
        // cout << q.front() << " ";
        for(int c=0; c<biggest; c++){
            if(matris[q.back()-1][c] == 1){
                // numOfPre[c]--;
                if(--numOfPre[c] == 0)
                    q.push(c+1);
            }
        }
    }
    cout << endl << "recommended: ";
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }


    return 0;
}
