#include <iostream>
#include <stack>
#include <sstream>
using namespace std;


int main(){
    stack<string> directory_stack;
    
    int n; cin >> n;
    for(int i=0; i<n; i++){
        string command; cin >> command;

        if(command == "cd"){
            string path; cin >> path;

            if(path[0] == '/'){
                int l = directory_stack.size();
                for(int j=0; j<l; j++)
                    directory_stack.pop();
            }

            stringstream ss(path);
            string directory;
            while(getline(ss, directory, '/'))
                if(!directory.empty()){
                    if(directory == ".."){
                        directory_stack.pop();
                    }
                    else
                        directory_stack.push(directory);
                }

        }
        else if(command == "pwd"){
            stack<string> tmp;
            int l = directory_stack.size();
            for(int j=0; j<l; j++){
                tmp.push(directory_stack.top());
                directory_stack.pop();
            }
            cout << "/";
            for(int j=0; j<l; j++){
                cout << tmp.top() << "/";
                directory_stack.push(tmp.top());
                tmp.pop();
            }
            cout << endl;
        }
    }

    return 0;
}