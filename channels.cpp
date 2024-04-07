#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    long long df, de;cin >> df >> de;
    int dis[10] = {0};
    for(int i=0; i<10; i++)
        cin >> dis[i];
    
    long long energy = df;
    string channels = "";
    for(int i=0; i<n; i++)
    {
        cin >> channels;
        for(int j=0; j<channels.length(); j++)
        {
            int ch = channels[j]-'0';
            energy += dis[ch];
        }
        energy += de;
    }
    cout << energy;

    
    return 0;
}