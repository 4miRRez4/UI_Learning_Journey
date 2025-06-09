// #include <iostream>
// using namespace std;
// // 1
// class cube{
//     public:
//     cube(int _x) { this->x = _x;}
//     cube& calculateLateralArea() { 
//         this->lateralArea = (6*x*x);
//         return *this;
//     }
//     int cost(int perUnit){
//         return perUnit*this->lateralArea;
//     }

//     private:
//     int x;
//     int lateralArea=0;

// };


// int main()
// {
//     cube myCube(2);
//     cout << myCube.calculateLateralArea().cost(3);
//     return 0;
// }

#include <iostream>
using namespace std;
//2
class cube{
    public:
    cube& setLength(int x) { 
        this->length =x;
        return *this;
    }
    cube& calculateLateralArea() { 
        this->lateralArea = (6*length*length);
        return *this;
    }
    cube& calculateCost(int perUnit){
        this->cost = this->lateralArea * perUnit;
        return *this;
    }
    void printCost() { cout << "cube cost is: " << cost;}
    private:
    int length;
    int lateralArea=0;
    int cost=0;
};

int main()
{
    cube myCube;
    myCube.setLength(2).calculateLateralArea().calculateCost(3).printCost();
    return 0;
}