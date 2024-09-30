#include <iostream>
#include <cmath>
class Circle{
    public:
    Circle() { x=0; y=0; radius=1; }
    Circle(int _x, int _y, double _radius) { x = _x, y=_x, radius=_radius;}
    Circle(Circle & c) { x=c.x, y= c.y, radius = c.radius;}

    void setX(int _x) { x=_x;}
    int getX() const {return x;}
    void setY(int _y) { y=_y;}
    int getY() const {return y;}
    void setRadius(double r) { radius=r;}
    double getRadius() const { return radius;}

    double getDiameter() const { return 2*radius;}
    double getCircumference() const {return 2*3.14*radius;}
    double getArea() const {return 3.14*radius*radius;}
    double getDistance() const {return sqrt(x*x + y*y);}
    void print() const;
    private:
    double radius;
    int x; 
    int y;
};
void Circle::print() const{
    std::cout << "x: " << x << " y:" << y << " radius: " << radius << std::endl;
    std::cout << "diameter: "<< this->getDiameter() << std::endl;
    std::cout << "circumference: "<< this->getCircumference() << std::endl;
    std::cout << "area: " << this->getArea() << std::endl;
    std::cout << "distance from origin: " << this->getDistance() << std::endl;
} 
int main(){
    Circle test(2,2,3);
    test.print();
    return 0;
}
