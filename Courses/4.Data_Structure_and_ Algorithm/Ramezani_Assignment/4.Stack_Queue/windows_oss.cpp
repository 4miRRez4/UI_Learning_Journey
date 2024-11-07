#include <iostream>
#include <sstream>
using namespace std;

int MAX_SIZE = 1000;
class Stack{
public:
    string* s;
    int top_ind;
    Stack(){
        top_ind = -1;
        s = new string[MAX_SIZE];
    }
    void push(string c){
        top_ind++;
        if(top_ind >= MAX_SIZE){
            string* newS = new string[2*MAX_SIZE];
            for(int i=0; i<MAX_SIZE; i++)
                newS[i] = s[i];
            delete[] s;
            s = newS;
            MAX_SIZE = MAX_SIZE*2;
        }
        s[top_ind] = c;
    }

    void pop(){
        if(top_ind >= 0)
            top_ind--;   
    }

    string top(){
        return (top_ind >= 0) ? s[top_ind]:" ";
    }

    bool empty(){
        return (top_ind == -1);
    }

    int size(){
        return top_ind+1;
    }

    ~Stack(){
        delete[] s;
    }
};

int main(){
    Stack* directory_stack = new Stack();
    
    int n; cin >> n;
    for(int i=0; i<n; i++){
        string command; cin >> command;

        if(command == "cd"){
            string path; cin >> path;

            if(path[0] == '/'){
                int l = directory_stack->size();
                for(int j=0; j<l; j++)
                    directory_stack->pop();
            }

            stringstream ss(path);
            string directory;
            while(getline(ss, directory, '/'))
                if(!directory.empty()){
                    if(directory == ".."){
                        directory_stack->pop();
                    }
                    else
                        directory_stack->push(directory);
                }

        }
        else if(command == "pwd"){
            Stack* tmp = new Stack();
            int l = directory_stack->size();
            for(int j=0; j<l; j++){
                tmp->push(directory_stack->top());
                directory_stack->pop();
            }
            cout << "/";
            for(int j=0; j<l; j++){
                cout << tmp->top() << "/";
                directory_stack->push(tmp->top());
                tmp->pop();
            }
            cout << endl;
        }
    }

    return 0;
}