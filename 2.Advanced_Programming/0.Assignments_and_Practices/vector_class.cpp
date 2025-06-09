#include <iostream>
#include <cmath>
using namespace std;

class Vector{
    public:
    Vector() : x(0), y(0) {}
    Vector(const Vector &v) { this->x=v.x; this->y=v.y;}
    ~Vector();

    bool operator<(const Vector& other);
    bool operator!=(const Vector& other) { return (this->x != other.x) && (this->y != other.y); }
    void operator-() { x=-x; y=-y;}

    int get_x() {return x;}
    int get_y() {return y;}
    void set_x(int newX) { x=newX;}
    void set_y(int newY) { y=newY;}

    private:
    int x;
    int y;
};
Vector::~Vector(){
    cout << "vector with x:" << x << " and y:" << y << " destructed." << endl;
}
bool Vector::operator<(const Vector& other){
    return sqrt((this->x*this->x) + (this->y*this->y)) < sqrt((other.x*other.x) + (other.y*other.y));
}

int main(){
    Vector defaultVector;
    cout << "x:" << defaultVector.get_x() << " y:" << defaultVector.get_y() << endl;
    defaultVector.set_x(2);
    defaultVector.set_y(4);
    Vector copyVector = defaultVector;
    cout << "x:" << copyVector.get_x() << " y:" << copyVector.get_y() << endl;
    copyVector.set_x(6);
    copyVector.set_y(8);
    cout << "x:" << copyVector.get_x() << " y:" << copyVector.get_y() << endl;

    if(defaultVector < copyVector)
        cout << "default vector is smaller than copy vector. " << endl;
    else
        cout << "default vector is not smaller that copy vector. " << endl;
    
    if(defaultVector != copyVector)
        cout << "default vector is not equal to copy vector. " << endl;
    else
        cout << "default vector is equal to copy vector. " << endl;

    -copyVector;
    cout << "after -: ";
    cout << "x:" << copyVector.get_x() << " y:" << copyVector.get_y() << endl;

    return 0;
}