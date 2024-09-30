#include <iostream>

class not_valid_type {};

class Temperature {
    public:
    Temperature() { cantigrad=18; }
    Temperature(float t) { cantigrad=t; }
    Temperature(Temperature& t1) { cantigrad=t1.cantigrad; }

    int convert(char type, int value){
        if(type == 'c')
            return (1.8*value) + 32;
        else if(type == 'f')
            return (value-32)/1.8;
        else
            throw not_valid_type();
    }
    private:
    float cantigrad;
};

int main()
{
    Temperature today;
    Temperature tomorrow(20);
    Temperature yesterday = tomorrow;

    try{
        char t; int v;
        std::cout << "enter type of temperature? (c->cantigrad, f->farenhite)" << std::endl;
        std::cin >> t;
        std::cout << "enter value of temperature? " << std::endl;
        std::cin >> v;
        std::cout << yesterday.convert(t, v) << std::endl;
    }catch (not_valid_type exc)
    {
        std::cout << "type invalid!!!" << std::endl;
    }

    return 0;
}