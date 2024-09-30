#include <iostream>
using namespace std;

class Worker{
    public:
    string DailyRoutine(){ return "Worker Doing daily routine... ";}
    virtual string getUp(){ return "Worker getting up... ";}
    virtual string eatBreakfast(){ return "Worker eatting breakfast... ";}
    virtual string goToWork(){ return "Worker going to work... ";}
    virtual string work(){ return "Worker doing work... ";}
    virtual string returnToHome(){ return "Worker returning to home... ";}
    virtual string relax(){ return "Worker relaxing... ";}
    virtual string sleep(){ return "Worker sleeping... ";}
};
class FireFighter : public Worker{
    public:
    string work(){ return "FireFighter doing work... ";}
};
class Lumberjack : public Worker{
    public:
    string work(){ return "Lumberjack doing work... ";}
};
class Postman : public Worker{
    public:
    string work(){ return "Postman doing work... ";}
};
class Manager : public Worker{
    public:
    string work(){ return "Manager doing work... ";}
    string relax(){ return "Manager relaxing... ";}
};

int main(){
    Manager mg;
    Postman pm;
    Lumberjack lj;
    FireFighter ff;
    Worker w;
    cout << w.DailyRoutine() << endl;
    cout << w.eatBreakfast() << endl;
    cout << mg.relax() << endl;
    cout << mg.work() << endl;
    cout << mg.eatBreakfast() << endl;
    cout << ff.work() << endl;
    cout << ff.goToWork() << endl;
    cout << pm.work() << endl;
    cout << pm.returnToHome() << endl;
    cout << lj.work() << endl;
    cout << lj.sleep() << endl;
    Worker *wptr;
    Manager mg2;
    wptr = &mg2;
    cout << wptr->relax() << endl;
    cout << wptr->eatBreakfast() << endl;
    return 0;
}