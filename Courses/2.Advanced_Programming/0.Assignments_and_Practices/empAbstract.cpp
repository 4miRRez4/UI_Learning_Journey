#include <iostream>
#include <vector>


class Employee {
    public:
    Employee(int wh) : workHour(wh) {};
    virtual int earning() = 0;
    protected:
    int workHour;
};
class Emp1 : public Employee{
    public:
    Emp1(int wh, int wrph) : Employee(wh), wageRatePerHour(wrph) {};
    virtual int earning() { return wageRatePerHour*workHour; }
    private:
    int wageRatePerHour;
};
class Emp2 : public Employee {
    public:
    Emp2(int wh, int cw) : Employee(wh), constWage(cw) {};
    virtual int earning() { 
        return (workHour <= 140) ? workHour*constWage : 140*constWage + (workHour-140)*1.5*constWage;
    }
    private:
    int constWage;
};

class Organization{
    public:
    void addEmp(Employee* emp){
        emps.push_back(emp);
    }
    int total_earnings(){
        int total =0;
        for(int i=0; i<emps.size(); i++)
            total += emps[i]->earning();
        return total;
    }
    private:
    std::vector<Employee*> emps;
};

int main()
{
    Emp1* e1 = new Emp1(150, 3000);
    Emp2* e2 = new Emp2(150, 3000);
    std::cout << e1->earning() << std::endl;
    std::cout << e2->earning() << std::endl;

    Organization og;
    og.addEmp(e1);
    og.addEmp(e2);
    std::cout << og.total_earnings() << std::endl;

    return 0;
}