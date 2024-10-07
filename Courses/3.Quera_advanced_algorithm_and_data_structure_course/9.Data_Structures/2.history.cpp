#include <iostream>
#include <stack>
using namespace std;

int main(){
    int q; cin >> q;
    string curr_history ="";
    for(int c=0; c<q; c++){
        string command, val; cin >> command;
        int l = command.length();
        int p;
        if(command[0] != 'u'){
            string place = "";
            int i = 7;
            while(command[i] != ' '){
                place += command[i];
                i++;
            }
            val = "";
            while(i < l){
                    val += command[i];
                    i++;
            }
            p = stoi(place);
        }

        switch(command[0]){
            case 'i':
                if(p > l){
                    curr_history += val;
                }else if(p == 1){
                    curr_history = val + curr_history;
                }else if(p > l/2){

                }else{
                    
                }
            case 'd':

            case 'u':
        }



    }

    return 0;
}