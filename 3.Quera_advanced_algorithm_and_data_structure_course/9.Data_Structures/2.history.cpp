#include <iostream>
#include <stack>
using namespace std;

int main(){
    int q; cin >> q;

    stack<string> history;
    history.push("");
    for(int i=0; i<q; i++){
        string command; cin >> command;

        string last_string = history.top();
        if(command == "insert"){
            int ind; cin >> ind; ind--;
            char ch; cin >> ch;
            for(int j=ind; j<last_string.size(); j++)
                swap(last_string[j], ch);
            last_string+=ch;

            history.push(last_string);
        }else if(command == "delete"){
            int ind; cin >> ind; ind--;

            string tmp_str = "";
            for(int j=0; j< last_string.size(); j++)
                if(j!=ind)
                    tmp_str += last_string[j];

            history.push(last_string);
        }else{
            history.pop();
        }

    }
    cout << history.top() << endl;


    return 0;
}