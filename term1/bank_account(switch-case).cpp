#include <iostream>

using namespace std;

int main()
{
    int balance = 0;
    
    do{
        cout << "please enter a mode: (b -> balance, w -> withdraw, i -> insert, q -> quit)" << endl;
        char operation;
        cin >> operation;
        
        switch(operation)
        {
            case 'b':
            {
                cout << "your balance: " << balance << endl;
                break;
            }
            case 'i':
            {
                cout << "please enter amount of money you want to insert in the bank sir: ";
                int cash;
                cin >> cash;
                
                balance += cash;
                cout << "your balance: " << balance << endl;
                break;
            }
            case 'w':
            {
                cout << "please enter amount of money you want to withdraw from the bank sir: ";
                int cash;
                cin >> cash;
                
                if(cash <= balance)
                {
                    balance -= cash;
                }else
                {
                    cout << "you don't have enough money, you poor thing.";
                }
                cout << "your balance: " << balance << endl;
                break;                
            }
            case 'q':
            {
                return 0;
            }
            default:
            {
                cout << "you didn't enter a fucking mode: (b -> balance, w -> withdraw, i -> insert, q -> quit)";
            }
            
        }
    }while(true);

}


