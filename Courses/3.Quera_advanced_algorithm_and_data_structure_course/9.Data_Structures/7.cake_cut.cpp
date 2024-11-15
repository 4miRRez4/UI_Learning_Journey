#include <iostream>
#include <set>
using namespace std;


int main(){
    int w, h, q; cin >> w >> h >> q;

    set<int> vertical_cuts;
    vertical_cuts.insert(0);
    vertical_cuts.insert(w);
    set<int> horizontal_cuts;
    horizontal_cuts.insert(0);
    horizontal_cuts.insert(h);

    multiset<int> vertical_lengths;
    vertical_lengths.insert(w);
    multiset<int> horizontal_lengths;
    horizontal_lengths.insert(h);

    for(int i=0; i<q; i++){
        char side; cin >> side;
        int coordinate, newPiece, newPiece2; cin >> coordinate;

        set<int>::iterator lb, find;
        if(side == 'V'){
            lb = vertical_cuts.lower_bound(coordinate);

            newPiece = *lb - coordinate;
            find = vertical_lengths.find(*lb - *(--lb));
            newPiece2 = coordinate - *lb;
            vertical_lengths.erase(find);

            vertical_lengths.insert(newPiece);
            vertical_lengths.insert(newPiece2);

            vertical_cuts.insert(coordinate);
        }
        else if(side == 'H'){
            lb = horizontal_cuts.lower_bound(coordinate);

            newPiece = *lb - coordinate;
            find = horizontal_lengths.find(*lb - *(--lb));
            newPiece2 = coordinate - *lb;
            horizontal_lengths.erase(find);

            horizontal_lengths.insert(newPiece);
            horizontal_lengths.insert(newPiece2);

            horizontal_cuts.insert(coordinate);
        }

        long long maxS = 1ll * (*(--vertical_lengths.end())) * (*(--horizontal_lengths.end()));
        cout << maxS << endl;
    }



    return 0;
}