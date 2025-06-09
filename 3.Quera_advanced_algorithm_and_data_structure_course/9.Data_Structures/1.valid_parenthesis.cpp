#include <iostream>
#include <stack>
using namespace std;

string parenthesis_pairs(string p, int len){
    // if((p[0] == ')') || (p[len-1] == '(') || (len%2 != 0))
    //     return "-1";
    
    stack<int> myStack;
    string answer = "";
    for(int i=0; i<len; i++){
        if(p[i] == '('){
            myStack.push(i+1);
        }else if(p[i] == ')'){
            if(myStack.size() == 0)
                return "-1";

            answer += to_string(myStack.top()) + " " + to_string(i+1) + "\n";
            myStack.pop();
        }
    }
    if(!myStack.empty()){
        return "-1";
    }

    return  answer;
}

int main(){
    string parenthesis; cin >> parenthesis;
    cout << parenthesis_pairs(parenthesis, parenthesis.length());
    return 0;
}