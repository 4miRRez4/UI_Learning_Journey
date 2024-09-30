//ap assignment
#include <iostream>
using namespace std;

class Shape{
    protected:
    string color;
    public:
    Shape(){ this->color = "default";  }
    Shape(string c) { this->color = c; }
    string get_color() { return this->color; }
    void set_color() { this->color = color; }
    string print() { return "color : " + this->color + '\n'; }
};
class Circle : public Shape{
    private:
    int radius;
    public:
    Circle() : Shape() { this->radius = 0;};
    Circle(string c, double r) : Shape(c) { this->radius = r; }
    int get_radius() { return this->radius; }
    void set_radius(int r) { this->radius = r; }
    int perimeter() { return 2*3.14*this->radius; }
    int area() { return 3.14*this->radius*this->radius; }
    string print();
};
string Circle::print(){
    string out = this->Shape::print();
    out += "perimeter : " + to_string(this->perimeter()) + '\n';
    out += "area : " + to_string(this->area()) + '\n';
    return out;
}
class Rectangle : public Shape{
    private:
    int height;
    int width;
    public:
    Rectangle();
    Rectangle(string c, double h, double w);
    int get_height() { return this->height; }
    int get_width() { return this-> width; }
    void set_height(int h) { this->height = h; }
    void set_width(int w) { this->width = w; }
    int perimeter() { return 2*(this->width + this->height); }
    int area() { return this->width * this->height; }
    string print();
};
Rectangle::Rectangle() : Shape() {
    this->height = this->width = 0;
}
Rectangle::Rectangle(string c, double h, double w) : Shape(c) {
    this->height = h;
    this->width = w;
}
string Rectangle::print(){
    string out = this->Shape::print();
    out += "perimeter : " + to_string(this->perimeter()) + '\n';
    out += "area : " + to_string(this->area()) + '\n';
    return out;
}

int main(){
    string mood; cin >> mood;
    if(mood == "Circle"){
        int radius; cin >> radius;
        string color; cin >> color;
        Circle cir(color, radius);
        cout << cir.print();
    }else if(mood == "Rectangle"){
        int width; cin >> width;
        int height; cin >> height;
        string color; cin >> color;
        Rectangle rec(color, height, width);
        cout << rec.print();
    }
    return 0;
}