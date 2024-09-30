#include <iostream>
using namespace std;

int main()
{
    int wolf, sheep, lettuce, boat; cin >> wolf >> sheep >> lettuce >> boat;
    if(boat == 0)
        cout << "SADKEK";
    else if((wolf == 0) && ((sheep < boat) || (sheep==boat && lettuce <= 2*boat) || (lettuce < boat) || (lettuce==boat && sheep <= 2*boat)))
        cout << "KEKW";
    else if(((lettuce == 0) && ((wolf < boat) || (wolf==boat && sheep <= 2*boat) || (sheep < boat) || (sheep==boat && lettuce <= 2*boat))))
        cout << "KEKW";
    else if(sheep == 0)
        cout << "KEKW";
    else if((sheep <= boat) && ((wolf+lettuce) <=2*boat))
        cout << "KEKW";
    else if(((wolf+lettuce) <= boat) && (sheep <= 2*boat))
        cout << "KEKW";
    else if((sheep < boat) || ((wolf+lettuce) <boat))
        cout << "KEKW";
    else
        cout << "SADKEK";

    return 0;
}