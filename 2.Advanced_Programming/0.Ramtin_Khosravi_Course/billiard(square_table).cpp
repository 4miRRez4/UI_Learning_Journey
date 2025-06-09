//simulation of billiard with oop concepts. https://ramtung.ir/apnotes/html/08_Billiards.html
#include<iostream>
#include<cstdlib>
using namespace std;

class Table
{
    public:
        Table(int w, int h);

        int get_width() {return width;}
        int get_height() {return height;}

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

class Ball
{
    public:
        Ball(int _x, int _y, int _vx, int _vy, Table* _ballTable);
        void move(int dt);

        int get_x() { return x; }
        int get_y() { return y; }
        int get_vx() { return vx; }
        int get_vy() { return vy; }
    private:
        int x;
        int y;
        int vx;
        int vy;
        Table* ballTable;
};
Ball::Ball(int _x, int _y, int _vx, int _vy, Table* _ballTable)
{
    if(_x < 0 || _x>_ballTable->get_width() || _y<0 || _y>_ballTable->get_height())
        abort();

    x = _x;
    y = _y;
    vx = _vx;
    vy = _vy;
}

void Ball::move(int dt) //ball movement in time dt
{
    x += vx * dt;
    y += vy * dt;
    while(x < 0 || x >= ballTable->get_width() || y < 0 || y >= ballTable->get_height())
    {   //doea the ball hit the frame of table
        if(x<0){
            x=-x;
            vx=-vx;
        }
        if(x>=ballTable->get_width()){
            x= 2*ballTable->get_width() - x; //width - (x-width)
            vx = -vx;
        }
        if(y<0){
            y = -y;
            vy = -vy;
        }
        if(y>=ballTable->get_height()){
            y = 2*ballTable->get_height() - y;
            vy = -vy;
        }
    }
}

int main()
{
    Table t(30,30);
    Ball myBall(10,5,3,2,&t);

    return 0;
}