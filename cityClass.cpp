//https://quera.org/course/assignments/65747/problems and https://quera.org/course/assignments/65747/problems/223323
//exercising with concepts of city as a class
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Unit
{
    public:
    Unit(int w, int h);
    int area(){ return this->height*this->width; }

    string get_name() { return ownerName;}
    void set_name(string name) { this->ownerName = name;}
    private:
    int width;
    int height;
    string ownerName;
};
Unit::Unit(int w, int h)
{
    if(w<=0 || h<=0)
        abort();
    width = w;
    height = h;
}

class Build
{
    public:
    void buildUnit(Unit* u);
    void sellUnit(string ownerName, int num);
    int get_numberOfUnits() { return this->numberOfUnits;}
    Unit* get_unit(int num) { return this->units[num-1];}
    private:
    int numberOfUnits=0;
    vector<Unit*> units;
};

void Build::buildUnit(Unit* u)
{
    units.push_back(u);
    numberOfUnits+=1;
}

void Build::sellUnit(string ownerName, int num)
{
    if(units[num-1]->get_name() == ownerName)
    {
        cout << "enter name of new owner: ";
        string name; cin >> name;
        units[num-1]->set_name(name);
    }
}

int main()
{
    Unit hafez15(500, 300);
    cout << hafez15.area() << endl;
    hafez15.set_name("amir");
    cout << hafez15.get_name() << endl;

    Build hafez;
    cout << hafez.get_numberOfUnits() << endl;
    hafez.buildUnit(&hafez15);
    cout << hafez.get_numberOfUnits() << endl;
    hafez.sellUnit("amir", 1);
    cout << hafez.get_numberOfUnits() << endl;
    cout << hafez.get_unit(1)->get_name() << endl;
    return 0;
}