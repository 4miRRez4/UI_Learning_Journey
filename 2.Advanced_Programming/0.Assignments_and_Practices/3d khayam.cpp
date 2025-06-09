//creating 3d array(row = khayam row, col = khayam col, height = khayam value)
#include <iostream>
using namespace std;

int permutation(int n, int k)
{
    // p(n, k) = n! / (n-k)! k! 
    int makhraj = 1;
    for(int i=k; i>0; i--)
        makhraj *= i;
    int sorat = 1;
    while(k!=0)
    {
        sorat *= n;
        n--;
        k--;
    }
    return sorat/makhraj;
}

int main()
{
    int rows; cin >> rows;
    int*** pascal = new int**[rows];//rows
    for(int r=0; r<rows; r++)
    {
        pascal[r] = new int*[r+1];//columns
        for(int c=0; c<r; c++)
        {
            int tmp = permutation(r, c);
            pascal[r][c] = new int[tmp];
        }
    }

}
