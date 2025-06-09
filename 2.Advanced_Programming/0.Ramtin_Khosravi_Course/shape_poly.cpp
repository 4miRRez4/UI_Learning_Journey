// https://ramtung.ir/apnotes/html/11_Inheritance.html
#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

class IllegalArgumentException {};

class Shape {
public:
    Shape(int init_x, int init_y) : x(init_x), y(init_y) {}
    int get_x() const { return x; }
    int get_y() const { return y; }
    void move(int dx, int dy);

    virtual void scale(int s) = 0;
    virtual void print() = 0;
    virtual int area() {return 0;};
protected:
    int x;
    int y;
};

void Shape::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

class Line : public Shape {
    public:
    Line(int init_x, int init_y, int l) : Shape(init_x, init_y), len(l) {};
    virtual void scale(int s) { len *= s;}
    virtual void print() { cout << "Line: " <<x<<","<<y<<","<<len<<endl;}
    private:
    // (x,y) center of line; len-> length of lien;
    int len;
};

class Triangle : public Shape {
    public:
    Triangle(int init_x, int init_y, int z) : Shape(init_x, init_y), zel(z) {};
    virtual void scale(int s) { zel *= s;}
    virtual void print();
    virtual int area() { return sqrt(3)/4 * zel*zel;}
    private:
    int zel;
};
void Triangle::print(){
    cout << "Triangle: " << x << ',' << y << ',' << zel << endl;
}

class Rect : public Shape {
public:
    Rect(int init_x, int init_y, int w, int h);
    virtual void scale(int s);
    virtual void print();
    virtual int area() { return this->width * this->height;}
private:
    int width;
    int height;
};

Rect::Rect(int init_x, int init_y, int w, int h)
    : Shape(init_x, init_y)
{
    if (w <= 0 || h <= 0)
	    throw IllegalArgumentException();
    width = w;
    height = h;
}

void Rect::scale(int s)
{
    width *= s;
    height *= s;
}

void Rect::print()
{
    cout << "Rect: " << x << ',' << y << ',' << width << ',' << height << endl;
}

class Circle : public Shape {
public:
    Circle(int init_x, int init_y, int r);
    virtual void scale(int s);
    virtual void print();
    virtual int area() { return 3.14*radius*radius;}
private:
    int radius;
};

Circle::Circle(int init_x, int init_y, int r)
    : Shape(init_x, init_y)
{
    if (r <= 0)
	    throw IllegalArgumentException();
    radius = r;
}

void Circle::scale(int s)
{
    radius *= s;
}

void Circle::print()
{
    cout << "Circle: " << x << ',' << y << ',' << radius << endl;
}

int main()
{
    vector<Shape*> shapes;
    
    while (true) {
        cout << "r. New Rectangle\n";
        cout << "c. New Circle\n";
        cout << "l. New Line\n";
        cout << "p. Display Shapes\n";
        cout << "m. Move All\n";
        cout << "s. Scale All\n";
        cout << "a. Area of all\n";
        cout << "q. Exit\n";
        
        char ch;    
        cin >> ch;
            
        if (ch == 'r') {
            int x, y, w, h;
            cout << "enter x, y, width, and height: ";
            cin >> x >> y >> w >> h;
            
            Rect *rect = new Rect(x, y, w, h);
            shapes.push_back(rect);
            
        } else if (ch == 'c') {
            int x, y, r;
            cout << "enter x, y, and radius: ";
            cin >> x >> y >> r;
            
            Circle *circ = new Circle(x, y, r);
            shapes.push_back(circ);
        
        }else if(ch == 'l'){
            int x,y,l;
            cout << "enter x, y, and length: ";
            cin >> x >> y >> l;

            Line* li = new Line(x, y, l);
            shapes.push_back(li);
        }else if (ch == 'p') {
            for (int i = 0; i < shapes.size(); i++)
                shapes[i]->print();
            cout<< endl;

        } else if (ch == 'm') {
            int dx, dy;
            cout << "enter dx, dy: ";
            cin >> dx >> dy;
            for (int i = 0; i < shapes.size(); i++)
                shapes[i]->move(dx, dy);
            
        } else if (ch == 's') {
            int s;
            cout << "enter s: ";
            cin >> s;
            for (int i = 0; i < shapes.size(); i++)
                shapes[i]->scale(s);
        }
        else if (ch == 'a'){
            for(int i=0; i<shapes.size(); i++)
                cout << shapes[i]->area() << endl;
        }
        else if (ch == 'q') {
            for (int i = 0; i < shapes.size(); i++)
                delete shapes[i];
            break;
        }
    } // while (true)
}	


// #include <iostream>
// #include <string>
// using namespace std;

// class object {
// public:
//     virtual int compare_to(const object* o) = 0;
//     virtual string to_string() const = 0;
// };

// class incomparable_types_ex {
// public:
//     incomparable_types_ex(const object* _o1, const object* _o2) : o1(_o1), o2(_o2) {}
//     const object* o1;
//     const object* o2;
// };

// class duck : public object {
// public:
//     duck(string n) : name(n) {}

//     int compare_to(const object* o) {
//         const duck* p = dynamic_cast<const duck*>(o);
//         if (p == NULL)
//             throw incomparable_types_ex(this, o);
//         return name.compare(p->name);
//     }
//     string to_string() const { return name; }
// private:
//     string name;
// };

// class student : public object {
// public:
//     student(string n, double d) : name(n), grade(d) {}

//     int compare_to(const object* o) {
//         const student* p = dynamic_cast<const student*>(o);
//         if (p == NULL)
//             throw incomparable_types_ex(this, o);
//         return grade - p->grade;
//     }

//     string to_string() const { return name; }
// private:
//     string name;
//     double grade;
// };

// int min_index(object* array[], int count, int from_index) {
//     int min_idx = from_index;
//     for (int i = 1; i < count; i++)
//         if (array[i]->compare_to(array[min_idx]) < 0)
//             min_idx = i;
//     return min_idx;
// }

// void selection_sort(object* array[], int count, int from_index) {
//     if (from_index >= count -1)
//         return;
//     int min_idx = min_index(array, count, from_index);
    
//     object* temp = array[min_idx];
//     array[min_idx] = array[from_index];
//     array[from_index] = temp;

//     selection_sort(array, count, from_index + 1);
// }

// int main() {
//     duck donald("Donald");
//     student moez("Moez", 2.0);

//     try {
//         cout << donald.compare_to(&moez);
//     } catch (incomparable_types_ex e) {
//         cerr << "Failed to compare incomparable objects: " 
//             << e.o1->to_string() << " and " << e.o2->to_string() << endl;
//     }

//     object* studs[] = {
//         new student("Masoud", 2.0),
//         new student("Gholam", 15.5),
//         new student("Ghamar", 17.8)
//     };

//     selection_sort(studs, sizeof(studs)/sizeof(object*), 0);

//     for (int i = 0; i < sizeof(studs)/sizeof(object*); i++) {
//         cout << studs[i]->to_string() << endl;
//         delete studs[i];
//     }
// }