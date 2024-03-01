//a boy at a want to date with a girl at b. road has two kinds of trains.
//one: stations at each integer
//two: stations at madareb k
//each train each to it's next station in one minute.
//we want minimum time that boy needs to reach the girl.
#include <iostream>
using namespace std;

long long find_nearest_station(long long k, long long location, long long destination)
{
    //finds nearest station kind two for given location
    long long station;
    if(location%k < k/2) //going to left station
    {
        station = (location/k) * k;
    }else if(location%k > k/2) //going to right station
    {
        station = ((location/k)+1) * k;
    }else//location is at middle, so we must go toward destination
    {
        station = (destination > location) ? ((location/k)+1) * k : (location/k) * k;
    }
    return station;
}

int main()
{
    long long k, a, b;
    while(cin >> k >> a >> b)
    {
        long long stations=0;
        //finding nearest train station kind two to a
        long long nearestStationA = find_nearest_station(k, a, b);

        stations += abs(a-nearestStationA);//number of station kind one needed to go to nearest station kind two

        //finding nearest train station kind two to b
        long long nearestStationB = find_nearest_station(k, b, a);

        stations += abs(b-nearestStationB);//number of station kind one needed to go to nearest station kind two

        //calculating number of stations needed between two stations
        stations += abs(nearestStationA-nearestStationB)/k;

        cout << stations << endl;

    }

    return 0;
}