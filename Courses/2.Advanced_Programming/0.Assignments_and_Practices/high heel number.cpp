//we want a number highHeel in range 0 to k(userInput), that sum of numbers before highHeel(1 and highHeel included) be equvalant to sum of highHeel and its next numbers: 6 => 1+2+3+4+5+6=6+7+8=21
#include <iostream>
using namespace std;

int sumOfBefore(int suspect)
{
    // int sum=0;
    // for(int i=0; i<=suspect; i++)
    //     sum+=i;
    // return sum;
    return (suspect*(suspect+1)) /2;
}

int main()
{
    int k;
    while(cin >> k)
    {   
            int beforeSum = sumOfBefore(k);//calculating sum before k

            int numberAfter = k;//variable for numbers ahead of k
            int suspectedSum = 0;//sum of i and numbers ahead of it
            while(suspectedSum < beforeSum)//iterating on numbers after k and adding them to suspectedSum and then compare it to beforeSum.(going until after sum is bigger)
            {
                suspectedSum += numberAfter;
                if(suspectedSum == beforeSum)
                {
                    cout << k << endl;
                }
                numberAfter++;
            }

        

    }

    return 0;
}