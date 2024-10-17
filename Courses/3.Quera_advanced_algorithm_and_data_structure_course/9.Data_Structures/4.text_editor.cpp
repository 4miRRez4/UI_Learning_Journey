#include <iostream>
#include <list>
using namespace std;

int main(){
    int q; cin >> q;
    list<char> text;
    list<char> ::iterator it = text.begin();
    
    for(int i=0; i<q; i++){
        string operation; cin >> operation;
        switch(operation[0]){
            case 'i':
                char ch; cin >> ch;
                text.insert(it, ch);
                break;
            case '+':
                if(it != text.end())
                    it++;
                break;
            case '-':
                if(it != text.begin())
                    it--;
                break;
        }
    }
    for(list<char> ::iterator it = text.begin(); it != text.end(); it++)
        cout << *it;

    return 0;
}