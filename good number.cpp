// برنامه‌ای بنویسید که یک عددk به عنوان ورودی از کاربر بگیرد و اولین عدد خوبی که حداقل k مقسوم‌علیه طبیعی دارد را به عنوان خروجی بدهد.

#include <iostream>
#include <cmath>
using namespace std;

int goodNumGenerator(int n)
{
    return n*(n+1)/2;
}

int divisorCounter(int num)
{
    int divisorCounter =1;
    for(int i=1; i<=num/2; i++)
    {
        if(num%i == 0)
            divisorCounter++;
    }
    return divisorCounter;
}


int main()
{
    int k; cin >> k;
    int numOfDivisors = 0, sentence =1, goodNum=1;
    while(numOfDivisors < k)
    {
        goodNum = goodNumGenerator(sentence);
        numOfDivisors = divisorCounter(goodNum);
        sentence++;
    }
    cout << goodNum;


    return 0;
}