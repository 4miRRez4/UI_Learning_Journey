#include <iostream>

class minus_length_exc {};

class Rectangle
{
public:
int a;
int b;
Rectangle(int a , int b);
bool isSquare();
};
Rectangle::Rectangle(int a, int b){
    if(a<0 || b<0)
        throw minus_length_exc();
    this->a = a;
    this->b = b;
}
bool Rectangle::isSquare(){
    if(this->a == this->b)
        return true;
    else
        return false;
}

int main()
{
    int width, height;
    std::cin >> width >> height;
    try{
        Rectangle newWindow(width, height);
        if(newWindow.isSquare())
            std::cout << ":))" << std::endl;
        else
            std::cout << "O_O" << std::endl;
    }catch(minus_length_exc exc){
        std::cout << "LENGTH CAN NOT BE MINUS!!!" << std::endl;
    }
    return 0;
}