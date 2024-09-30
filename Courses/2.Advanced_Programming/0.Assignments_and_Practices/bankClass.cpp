//https://quera.org/course/assignments/65523/problems/222379
//dealing with bank management concept with oop approach
#include <iostream>
using namespace std;

enum accountType {SAVING_ACC, SALARY_ACC, NRI};
enum loanType {BUISSINESS = 7000, STUDENT = 2000, MORTGAGE = 5000, MARRIAGE = 4000};

class Account
{
    public:
        Account(string _name, int _nationalCode, string _cityName, int _bankBranch, int _balance, accountType _at);
        Account(string _name, int _nationalCode, int _bankBranch, int _balance, accountType _at);
        Account(string _name, int _nationalCode, int _bankBranch, accountType _at);

        void checkAccountBalance();
        void withdraw(int amount);
        void deposit(int amount);
        void profitCalculation();
        void loanRequest(string _name, int _nationalCode, int amount);
        void loanRequest(string _name, int _nationalCode, loanType _lt);
    private:
        string name;
        int nationalCode;
        string cityName;
        int bankBranch;
        int balance;
        accountType at;
        int accountScore =0;
        loanType lt;
        int loanMoney;
};
Account::Account(string _name, int _nationalCode, string _cityName, int _bankBranch, int _balance, accountType _at)
{
    name = _name;
    nationalCode = _nationalCode;
    cityName = _cityName;
    bankBranch = _bankBranch;
    balance = _balance;
    at = _at;
}
Account::Account(string _name, int _nationalCode, int _bankBranch, int _balance, accountType _at)
{
    Account(_name, _nationalCode, "Esfahan", _bankBranch,  _balance, _at);
}
Account::Account(string _name, int _nationalCode, int _bankBranch, accountType _at)
{
    Account(_name, _nationalCode, "Esfahan", _bankBranch,0, _at);
}

void Account::checkAccountBalance()
{
    balance += (at == SALARY_ACC) ? -1:-2;
    cout << "your bank account balance : " << balance << endl;
    if(balance <=2)
        cout << "You are Very Poor!!!" << endl;
    else
    {
        accountScore += 10;
    }
}

void Account::withdraw(int amount)
{
    if(amount > 10000)
        cout << "The Withdraw Limit is $10000"<< endl;
    else if(amount > balance)
        cout << "Your Accout Balance is not Enough"<< endl;
    else
    {
        balance-= amount;
        accountScore += 20;
        cout << "Withdrawal Completed Successfully." << endl;
    }
}

void Account::deposit(int amount)
{
    if(amount > 1000)
    {
        cout << "The Deposit Limit is $1000" << endl;
        balance -= 0.01*balance;
        cout << "you are charged 1 percent. new balance: " << balance << endl;
    }else
    {
        balance += amount;
        accountScore+=30;
        cout << "deposit was made successfully." << endl;
    }
}

void Account::profitCalculation()
{
    cout << "your profit is: " ;
    if(at == SAVING_ACC)
        cout << 0.1*balance << endl;
    else
        cout << 0.02*balance << endl;
}

void Account::loanRequest(string _name, int _nationalCode, int amount)
{
    if(_name != name || _nationalCode!= nationalCode)
        cout << "Account Not Found!!!"<<endl;
    else if(balance < amount/2)
        cout << "Your Credit is not Enough for This Loan" << endl;
    else if(accountScore < 100)
        cout << "You don't Have Enough Score!!!" << endl;
    else if(amount > 500)
        cout << "Loan Limit is $500." << endl;
    else
    {
        cout << "Loan Application Applied Successfully." << endl;
        balance += amount;
    }
}

void Account::loanRequest(string _name, int _nationalCode, loanType _lt)
{
    if(_name != name || _nationalCode!= nationalCode)
        cout << "Account Not Found!!!"<<endl;
    else    
    {
        cout << "Loan Application Applied Successfully." << endl;
        lt = _lt;
        switch(_lt)
        {
            case loanType::BUISSINESS :
            {
                loanMoney = static_cast<int>(loanType::BUISSINESS);
                break;
            }
            case loanType::STUDENT :
            {
                loanMoney = static_cast<int>(loanType::STUDENT);
                break;
            }
            case loanType::MORTGAGE :
            {
                loanMoney = static_cast<int>(loanType::MORTGAGE);
                break;
            }
            case loanType::MARRIAGE :
            {
                loanMoney = static_cast<int>(loanType::MARRIAGE);
                break;
            }
            default:
            {
                cout << "not valid loan type!!"<<endl;
                return;
            }
        }
        balance += loanMoney;
    }
}

int main()
{
    Account acc1("Ftm", 123, "Tehran", 11, 50000, SAVING_ACC);
    acc1.checkAccountBalance();
    acc1.withdraw(5000);
    acc1.deposit(1000);
    acc1.deposit(500);
    acc1.deposit(7000);
    acc1.checkAccountBalance();
    acc1.profitCalculation();
    acc1.loanRequest("Ftm", 124, 400);
    acc1.loanRequest("Ftm", 123, 400);
    acc1.loanRequest("Ftm", 123, BUISSINESS);
    acc1.checkAccountBalance();

    return 0;
}