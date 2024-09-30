#include <iostream>
class Emp {
    public:
    Emp(std::string n, int hour) { name =n; nWork =hour;}
    void set_name(std::string n) { name = n;}
    void set_nWork(int hour) { nWork = hour;}
    long long tax(int monthly){
        if(monthly < 10000000)
            return 0;
        else if(monthly < 20000000)
            return 10/100 * monthly;
        else //more than 20000000
            return 15/100 * monthly;
    }
    long long salary(){
        long long s = nWork * 93750;
        if(nWork < 154)
            s *= 80/100;
        else if(nWork > 181)
            s += (nWork-181) * 93750 * 140/100;

        return s-tax(s);
    }   
    private:
    std::string name;
    int nWork;
};

int main()
{

    return 0;
}