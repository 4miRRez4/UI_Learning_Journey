//least change paper with 100, 20, 10, 5 ,1 dollar cash
#include <iostream>
using namespace std;


int main()
{
    int amount; cin >> amount;
    int hundred=0, twenty=0, ten=0, five=0, one=0;

    if(amount >= 100)
    {
        hundred = amount/100;
        amount = amount%100;
    }
    if(amount >=20){
        twenty = amount/20;
        amount = amount%20;
    }
    if(amount >=10){
        ten = amount/10;
        amount = amount%10;
    }
    if(amount >=5){
        five = amount/5;
        amount = amount%5;
    }
    one = amount;

    std::cout << hundred << twenty << ten << five << one << endl;
    std::cout << hundred+twenty+ten+five+one;
    return 0;
}