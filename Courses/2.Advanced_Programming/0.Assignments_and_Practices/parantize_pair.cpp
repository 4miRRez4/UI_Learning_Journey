//input: (()())()
//output: 63254187
#include <iostream>
#include <stack>
using namespace std;

int main(){
    char s[100];
    scanf("%s", s);
    string str = s;

    stack<int> st;
    int out[str.length()]={};
    for(int i=0; i<str.length(); i++){
        if(str[i] == '('){
            st.push(i);
        }else{
            out[i] = st.top();
            out[st.top()] = i;
            st.pop();
        }
    }
    for(int i=0; i<str.length(); i++)
        cout << out[i]+1;


    return 0;
}