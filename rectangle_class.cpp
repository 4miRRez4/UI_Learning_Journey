#include <iostream>
using namespace std;

class Rectangle
{
    public:
    Rectangle(double w, double h)
    {
        if(w<0 || h<0)
            cout << "NoT VaLiD!!!"<<endl;
        else
        {
            this->width = w;
            this->height = h;
        }
    }
    double  area() { return width*height;}
    double environment() { return 2*(width+height);}

    private:
    double width;
    double height;
};


int main()
{
    double width, height;
    cout << "plz enter width and height:(\"exit\" for exit) " << endl;
    while(cin >> width >> height)
    {
        Rectangle newRec(width, height);
        cout << "area is: " << newRec.area() << endl;
        cout << "environment is: " << newRec.environment() << endl;
        
        cout << "plz enter width and height:(\"exit\" for exit) " << endl;

    }


    return 0;
}