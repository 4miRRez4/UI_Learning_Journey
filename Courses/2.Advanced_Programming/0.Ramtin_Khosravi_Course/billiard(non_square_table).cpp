//simulation of billiard with oop concepts. https://ramtung.ir/apnotes/html/08_Billiards.html
#include<iostream>
#include<cstdlib>
using namespace std;

class Ball;//this is just declaration so that table class knows there is something like Ball.

class Table //we don't want to suppose that table is square, because with that we are changing the world of problem.
{
    public:
        Table(int w, int h); //constructor
        bool contains_point(int x, int y); //is point in the table? (in this approach we are limiting assosiasion and we want privacy more. Table just recievs a messege from something(doesn't matter what) and return if that thing is in it)
        void reflect(Ball* b);//fixing state of thing that is out of table
    
    private:
        int width;
        int height;
};
Table::Table(int w, int h)
{
    if(w<0 || h<0)
        abort();
    width = w;
    height = h;
}

bool Table::contains_point(int x, int y)
{
    return x>=0 && x<=width && y>=0 && y<=height;
}

void Table::reflect(Ball* b)
{
    int x = b->get_x();
    int y = b->get_y();
    int vx = b->get_vx();
    int vy = b->get_vy();

    if (x < 0) {
        x = -x;
        vx = -vx;
    }
    if (x >= width) {
        x = 2 * width - x;
        vx = -vx;
    }
    if (y < 0) {
        y = -y;
        vy = -vy;
    }
    if (y >= height) {
        y = 2 * height - y;
        vy = -vy;
    }

    b->set_location(x, y);
    b->set_speed(vx, vy);
}

class Ball
{
    public:
        Ball(int _x, int _y, int _vx, int _vy, Table* t);
        void move(int dt);
        //getters:
        int get_x() { return x; }
        int get_y() { return y; }
        int get_vx() { return vx; }
        int get_vy() { return vy; }
        //setters:
        void set_location(int _x, int _y);
        void set_speed(int _vx, int _vy);
    private:
        int x;
        int y;
        int vx;
        int vy;
        Table* table;
};
Ball::Ball(int _x, int _y, int _vx, int _vy, Table* t)
{
    table = t;
    set_location(_x, _y);
    set_speed(_vx, _vy);
}

void Ball::set_location(int _x, int _y) {
    if (!table->contains_point(_x, _y))
        abort();
    x = _x;
    y = _y;
}

void Ball::set_speed(int _vx, int _vy) {
    vx = _vx;
    vy = _vy;
}

void Ball::move(int dt)
{
    x += vx * dt;
    y += vy * dt;
    
    while (!table->contains_point(x, y))
        table->reflect(this);
}

int main()
{
    Table t(100, 50);
    Ball b(10, 20, 25, 5, &t);
    b.move(10); 

    return 0;
}