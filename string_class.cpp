#include <iostream>
using namespace std;

class z_string
{
    private:
    char* str;
    int size;
    public:
    z_string(char* s,int size);
    int getSize();
    int compareTo(z_string str);
    void print();
};
z_string::z_string(char* s, int size)
{
    this->size = size;
    str = s;
}
int z_string::getSize()
{
    return this->size;
}
int z_string::compareTo(z_string str)
{
    int minSize = (this->size < str.getSize()) ? this->size:str.getSize();
    for(int i=0; i<minSize; i++)
    {
        if(this->str[i] > str.str[i])
            return 1;
        if(this->str[i] < str.str[i])
            return -1;
    }
    if(this->size == str.getSize()) return 0;
    return (this->size < str.getSize()) ? 1:-1;
}
void z_string::print(){
    cout << this->str << endl;
}

int main()
{
    int s1; 
    cin >> s1;
    char* str1 = new char[s1];
    cin >> str1;
    int s2;
    cin >> s2;
    char* str2 = new char[s2];
    cin >> str2;

    z_string z1(str1, s1);
    z_string z2(str2, s2);

    int compared = z1.compareTo(z2);
    if(compared == 0)
        cout << "Yek==Do";
    else 
        cout << ((compared > 0) ? "Yek>Do":"Yek<Do");

    return 0;
}