#include <iostream>
using namespace std;

class Student
{
    public:
    // void set_name(string n) { this->name = n;}
    // void set_studentNum(string num) { this->studentNum = num;}
    // void set_average(float avg) { this->average = avg;}
    // float get_average() { return this->average;}
    // string get_studentNum() { return this->studentNum;}
    // private:
    string name;
    string studentNum;
    float average = 0;
};
float calAvg(Student* stds, int len)
{
    float sum=0;
    for (int i = 0; i < len; i++)
        sum += stds[i].average;
    return sum/len;
}
void sort(Student* rejected, int numOfRejected)
{
    Student tmp;
    for (int i=0; i<numOfRejected; i++)
        for (int j=i+1; j<numOfRejected; j++)
            if (rejected[i].average > rejected[j].average)
            {
                tmp = rejected[i];
                rejected[i] = rejected[j];
                rejected[j] = tmp;
            }
}
int main()
{
    int len = 1;
    Student* stds = new Student[len];
    
    string in; Student tmp; string tmpNum; float tmpAvg; Student* newArr;
    while(true)
    {
        cin >> in;
        if(in == "end") break;

        // tmp.set_name(in);
        // cin >> tmpNum;
        // tmp.set_studentNum(tmpNum);
        // cin >> tmpAvg;
        // tmp.set_average(tmpAvg);
        tmp.name = in;
        cin >> tmp.studentNum;
        cin >> tmp.average;

        newArr = new Student[len];
        for (int i=0; i<len-1; i++)
                newArr[i] = stds[i];
        newArr[len-1] = tmp;
        delete[] stds;
        stds = new Student [len];
        for(int i=0; i<len; i++)
            stds[i] = newArr[i];
        delete[] newArr;

        len++;
    }

    float average=calAvg(stds, len-1);

    Student* rejected = new Student[len-1];
    int numOfRejected = 0;
    for(int i=0; i<len-1; i++)
        if (stds[i].average < average)
        {
            rejected[numOfRejected] = stds[i];
            numOfRejected++;
        }

    sort(rejected, numOfRejected);


    cout << fixed; cout.precision(2);
    cout << average << endl;
    int i = 0;
    while(rejected[i].average != 0)
    {
        cout << rejected[i].studentNum << endl;
        i++;
    }


    delete[] stds;
    delete[] rejected;
    return 0;
}
