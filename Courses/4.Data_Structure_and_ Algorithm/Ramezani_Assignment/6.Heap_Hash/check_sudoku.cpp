#include <iostream>
#include <unordered_set>
using namespace std;

bool isValid(int table[9][9]){
    unordered_set<int> rows[9];
    unordered_set<int> cols[9];
    unordered_set<int> subs[9];

    for(int r=0; r<9; r++)
        for(int c=0; c<9; c++){
            int box_val = table[r][c];

            if(box_val == 0) continue;

            //check the row
            if(rows[r].find(box_val) != rows[r].end())
                return false;
            rows[r].insert(box_val);

            //check the column
            if(cols[c].find(box_val) != cols[c].end())
                return false;
            cols[c].insert(box_val);

            //check the 3*3 sub box
            int sub_ind = (r/3)*3 + c/3;
            if(subs[sub_ind].find(box_val) != subs[sub_ind].end())
                return false;
            subs[sub_ind].insert(box_val);
        }

        return true;
}

int main(){
    int table[9][9];
    char box;
    for(int r=0; r<9; r++)
        for(int c=0; c<9; c++){
            cin >> box;
            if(box == '-') 
                table[r][c] = 0;
            else    
                table[r][c] = box - '0';
        }

    
    if(isValid(table))
        cout << "Valid" << endl;
    else
        cout << "Invalid" << endl;


    return 0;
}