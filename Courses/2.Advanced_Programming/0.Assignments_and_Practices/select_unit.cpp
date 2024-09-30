//https://quera.org/course/assignments/66010/problems/224507
//unit selection simulation with oop conceps

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class University
{
    public:
    void addingLesson(Lesson l) { if(lessons.size() <11) lessons.push_back(l); }
    void addingSection(Section s, int lessonInd) { sections[lessonInd].push_back(s); }
    void addingStudent(Student s) { students.push_back(s); }
    string printUniLessons();
    private:
    vector<Lesson> lessons;
    vector<Student> students;
    const string uniName = "ISFAHAN";
    vector<vector<Section>> sections;
};
string University::printUniLessons()
{
    string out = "";
    for(int i=0; i<lessons.size(); i++)
    {
        out += lessons[i].name;
        out += "\n";
    }
    return out;
}

University uni;

class Section
{
    public:
    Section(Lesson l, int c, int o) : lesson(l), capacity(c), obtainedStudents(o) { code = lesson.get_name() + to_string(lesson.get_unitNum()) + to_string(capacity);};
    string display_info();
    void addingFromWaiting();
    private:
    Lesson lesson;
    vector<Student> stds;
    vector<Student> waiting;
    int capacity;
    int obtainedStudents;
    string code;

    friend class Student;
};
string Section::display_info()
{
    string info = "";
    info += "name: " + lesson.get_name() + '\n';
    info += "capacity : " + to_string(capacity) + '\n';
    info += "obtainde stds: " + to_string(obtainedStudents) + '\n';
    info += "code: " + code + '\n';
}
void Section::addingFromWaiting()
{
    if(waiting.size() != 0 && stds.size() < capacity)
    {    
        stds.push_back(waiting[0]);
        waiting.erase(waiting.begin());
    }
}

enum lessonKind {MAJOR, ELECTIVE, LAB, CORE};
class Lesson
{
    public:
    string lesson_info();
    string get_name() { return name;}
    int get_unitNum() { return unitNum;}
    private:
    string name;
    int unitNum;
    lessonKind lk;
};
string Lesson::lesson_info()
{
    string info = "";
    info += "name: " + name + '\n';
    info += "unit number: " + to_string(unitNum) + '\n';
    info += "lesson kind: " + to_string(lk) + '\n';
    return info;    
}

enum facultyCode {COMPUTER=36, CHEMISTRY=32, ECONOMIC=19};
enum faculties {COMPUTER, ENGINEERING, LITERATURE, MATH, PHYSICS, CHEMISTRY};
class Student
{
    public:
    Student(string _name, int _avg, faculties _faculty, int _enter_year);
    string student_sections();
    string student_info();

    private:
    int std_num;
    string name;
    int enter_year;
    faculties faculty;
    float avg;
    int maxUnits;
    vector<Section> sections;
    int sectionsObtained;
    vector<Section> waiting_sections;
};
Student::Student(string _name, int _avg, faculties _faculty, int _enter_year)
{
    if(_avg < 0 || _avg >20)
    {
        cout << "INVALID average!!!" << endl;
        return; 
    }
    name = _name;
    avg = _avg;
    faculty = _faculty;
    enter_year = _enter_year;
    sectionsObtained = 0;

    if(avg <12) maxUnits =3;
    else if(avg <=17) maxUnits =5;
    else maxUnits = 7;
}


string Student::student_sections()
{
    string message = "";
    message += "your obtained sections are: \n";   
    for(int i=0; i<sectionsObtained; i++)
        message += (sections[i].lesson.get_name() + "\n");

    message += "your waiting sections are: \n";
    for(int i=0; i<waiting_sections.size(); i++)
        message += (waiting_sections[i].lesson.get_name() + "\n");

    return message;
}

string Student::student_info()
{
    string info = "";
    info += "student number: " + to_string(std_num) + "\n";
    info += "name: " + name + "\n";
    info += "enter year: " + to_string(enter_year) + "\n";
    info += "faculty: " + to_string(faculty) + "\n";
    info += "average: " + to_string(avg) + "\n";
    info += student_sections() + "\n";
    return info;
}


int main()
{



    return 0;
}