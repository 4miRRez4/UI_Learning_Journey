#include <iostream>
using namespace std;

class Name {
    private:
    string first;
    string last;
    string nick;
    public:
    Name(string f, string l, string n) : first(f), last(l), nick(n) {
        cout << "welcome " << first << " " << last << ".";
        cout << "(known as " << nick << ")" << endl;
    }
};

class Person {
    private:
    Name name;
    string bd;
    string degree;
    public:
    Person(Name _name, string _bd, string _degree) : name(_name), bd(_bd), degree(_degree) {};
};

class Address: public Person {
    private:
    string country;
    string state;
    string city;
    string street;
    public:
    Address(string _first, string _last, string _nick,
            string _bd, string _degree, 
            string _country, string _state, string _city, string _street)
            : Person(Name(_first, _last, _nick), _bd, _degree),
              country(_country), state(_state), city(_city), street(_street) {}
};

int main() {
    Address ad("mohamad", "fatemi", "potato", "1370/2/14", "phd", "iran", "tehran", "tehran", "sadi");

    return 0;
}
