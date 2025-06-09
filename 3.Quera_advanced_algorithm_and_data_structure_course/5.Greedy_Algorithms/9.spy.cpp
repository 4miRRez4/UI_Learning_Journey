#include <iostream>
#include <set>
using namespace std;

int main(){
    int n; cin >> n;
    getchar();
    string dont_care;
    for(int i=0; i<n; i++)
        getline(cin, dont_care);

    int q; cin >> q;
    getchar();
    int num_of_move = 0;
    set<string> organizations;
    string orga;
    for(int i=0; i<q; i++){
        getline(cin, orga);
        organizations.insert(orga);
        if(n == organizations.size()){
            num_of_move++;
            organizations.clear();
            organizations.insert(orga);
        }
    }

    cout << num_of_move << endl;
    return 0;
}