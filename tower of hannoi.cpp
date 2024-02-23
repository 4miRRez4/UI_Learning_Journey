#include <iostream>
#include <vector>
using namespace std;

/*3 steps of recursive problems:
1=>base case: simplest form of problem(in this one moving one disk)
2=>solving problem for f(n-1) (moving n-1 disks to auxiliruty rod)
3=>solving f(n) based on f(n-1) (moving biggest rod to destination rod and then moving n-1 disks from aux to destination rod)
*/

// definition of the three pegs
vector<int> a;
vector<int> b;
vector<int> c;

void print_rod(vector<int> rod)
{
    for (int i = 0; i < rod.size(); i++)
        cout << rod[i] << ' ';
    cout << '\n';
}

void print_rods()
{
    cout << "A: ";
    print_rod(a);
    cout << "B: ";
    print_rod(b);
    cout << "C: ";
    print_rod(c);
    cout << endl;
}

void move(vector<int>& from, vector<int>& to)
{
    to.push_back(from.back());
    from.pop_back();
    print_rods();
}

void towerOfHannoi(int n, vector<int>& from, vector<int>& to, vector<int>& aux)
{
    //base case
    if(n == 1)
        move(from, to);
    else
    {
        towerOfHannoi(n-1, from, aux, to);
        move(from, to);
        towerOfHannoi(n-1, aux, to, from);
    }
}

int main()
{
    int num_of_discs;
    cout << "How many discs? ";
    cin >> num_of_discs;

    for (int i = num_of_discs; i >= 1; i--)
        a.push_back(i);

    print_rods();
    towerOfHannoi(num_of_discs, a, c, b);

    return 0;
}