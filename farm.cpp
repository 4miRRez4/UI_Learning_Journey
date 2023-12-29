#include <iostream>
using namespace std;

void peakL(int a[], int j, bool &leftL)
{
    //iterating on left elements and checking being ascending;
    leftL = true;
    for(int k=0; k<j; k++)
    {
        if(a[k] > a[k+1] )
        {
            leftL = false;
            break;
        }
    }

}
void peakR(int a[], int j, int n, bool &rightL)
{
    //iterating on left elements and checking being descending;
    rightL = true;
    for(int k=n-1; k>j; k--)
    {
        if(a[k] >= a[k-1])
        {
            rightL = false;
            break;
        }
    }
}

void valleyL(int a[], int j, bool &leftL)
{
    //iterating on left elements and checking being descending;
    leftL = true;
    for(int k=0; k<j; k++)
    {
        if(a[k] < a[k+1] )
        {
            leftL = false;
            break;
        }
    }

}
void valleyR(int a[], int j, int n, bool &rightL)
{
    //iterating on left elements and checking being ascending;
    rightL = true;
    for(int k=n-1; k>j; k--)
    {
        if(a[k] <= a[k-1])
        {
            rightL = false;
            break;
        }
    }
}
int main() {
    int n;
    cin >> n;

    int height[n];
    for(int i=0; i<n; i++)
    {
        cin >> height[i];
    }

    bool  leftL = true;
    bool rightL = true;

    //iterating on elements and checking the condition;
    for(int j=0; j<n; j++)
    {
        //checking condition existing a peak;
        peakL(height, j, leftL);
        peakR(height, j, n, rightL);

        if(leftL && rightL)
        {
            cout << "Yes";
            return 0;
        }

        //checking condition existing a valley;
        valleyL(height, j, leftL);
        valleyR(height, j, n, rightL);

        if(leftL && rightL)
        {
            cout << "Yes";
            return 0;
        }

    }
    cout << "No";

}
