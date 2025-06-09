#include <iostream>
using namespace std;

int sumOfDigits(int num)
{
    if(num == 0) return 0;//base case
    else return num%10 + sumOfDigits(num/10);//recursive base

}

int beingLonely(int num)
{
    //takes a number and calculates sum of digits until answer is less than 10(recursively);

    //base case: being less than 10;
    if(num < 10)
    {
        return num;
    }else
    {
        //sum of digits;
        int sum = sumOfDigits(num);

        //recusive case:
        return beingLonely(sum);
    }


};

int main() {
    int n; cin >>n;

    cout << beingLonely(n);
    return 0;
}
