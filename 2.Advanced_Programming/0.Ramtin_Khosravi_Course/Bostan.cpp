//implementation of bostan(like golestan.ui.ac.ir) for fifth assignment of ramtin khosravi ap
#include <iostream>
#include <vector>
using namespace std;

struct lessonName
{
    string lName;
};

struct lesson
{
    lesson(int _numOfUnits, int _term, int _grade, string _status, lessonName* _lName);
    lessonName* lName;
    int numOfUnits;
    int term;
    float grade;
    string status="unknown";
};
lesson::lesson(int _numOfUnits, int _term, int _grade, string _status, lessonName* _lName)
{
    numOfUnits = _numOfUnits;
    term = _term;
    grade = _grade;
    status = _status;
    lName = _lName;
}

struct reportCard
{
    reportCard(int _avg, int _conditionalTerms, int _sonsecutiveConditionalTerms, int _passedUnits, lesson* _lesson);
    int isThereLesson(string l)
    {
        for(int i=0; i<lessons.size(); i++)
        {
            if(lessons[i]->lName->lName == l)
            {
                return i;
            }
        }
        return -1;
    }
    int avg;
    int conditionalTerms;
    int consecutiveConditionalTerms;
    int passedUnits;
    vector<lesson*> lessons;
};
reportCard::reportCard(int _avg, int _conditionalTerms, int _sonsecutiveConditionalTerms, int _passedUnits, lesson* _lesson)
{
    avg = _avg;
    conditionalTerms = _conditionalTerms;
    consecutiveConditionalTerms =consecutiveConditionalTerms;
    passedUnits = _passedUnits;
    lessons.push_back(_lesson);
}

class student
{
    public:
    student(string n, int nc, int bd, int sn, int ey, reportCard* _rp);
    reportCard* rp;

    int get_studentNumber(){ return studentNumber;}
    string get_name() { return name;}
    int get_nationalCode() { return nationalCode;}
    int get_birthDate() { return studentNumber;}
    int get_enteringYear() { return enteringYear;}

    private:
    string name;
    int nationalCode;
    int birthDate;
    int studentNumber;
    int enteringYear;
};
student::student(string n, int nc, int bd, int sn, int ey, reportCard* _rp)
{
    name = n;
    nationalCode = nc;
    birthDate = bd;
    studentNumber = sn;
    enteringYear = ey;
    rp = _rp;
}

class Bostan
{
    public:
    int isThereStudent(int stdNum);
    void enterGrade(int stdNum, string lessonName, int unitNum, int grade);
    void get_StdInfo();
    void addStudent(student* std);
    vector<student*> get_students() { return students;}
    private:
    vector<student*> students;
};

void Bostan::addStudent(student* std)
{
    students.push_back(std);
}

int Bostan::isThereStudent(int stdNum)
{
    for(int i=0; i<students.size(); i++)
    {
        if(students[i]->get_studentNumber() == stdNum)
        {
            return i;
        }
    }
        return -1;
}

void Bostan::enterGrade(int stdNum, string lName, int unitNum, int grade)
{
    int tmp = isThereStudent(stdNum);
    if(tmp != -1)
    {
        tmp = students[tmp]->rp->isThereLesson(lName);
        if(tmp != -1)
        {
            students[tmp]->rp->lessons[tmp]->grade = grade;
        }else
        {
            cout << "you're entering grade for new lesson.";
            int t;
            cout << "enter term: "; cin >> t;
            string status = (grade>=14) ? "passed":"not-passed";
            lessonName ln; ln.lName = lName;
            lesson newLesson(unitNum, t, grade, status, &ln);
            students[tmp]->rp->lessons.push_back(&newLesson);
        }
    }
}

void Bostan::get_StdInfo()
{
    cout << "please enter student number: ";
    int stdNum; cin >> stdNum;
    int stdIndex = isThereStudent(stdNum);
    if(stdIndex!=-1)
    {
        cout << "name: " << students[stdIndex]->get_name() << endl;
        cout << "national code: " << students[stdIndex]->get_nationalCode() << endl;
        cout << "average: " << students[stdIndex]->rp->avg << endl;
        cout << "number of conditional term: " << students[stdIndex]->rp->conditionalTerms << endl;
        cout << "number of consecutive conditional term: " << students[stdIndex]->rp->consecutiveConditionalTerms << endl;
        cout << "all unit passed: " << students[stdIndex]->rp->passedUnits << endl;
    }else
        cout << "There's no student with given student number";
}

int main()
{
    Bostan golestan;
    lessonName l; l.lName = "AP";
    lesson ls(3, 2, 20, "passed", &l);
    reportCard myRp(20, 0, 0, 16, &ls);
    student std("AmirrezA", 372748, 1383, 402361, 1402, &myRp);
    golestan.addStudent(&std);
    cout << golestan.get_students()[0]->get_name() << endl;
    golestan.get_StdInfo();
    golestan.enterGrade(402361, "ap", 3, 19);
    cout << golestan.get_students()[0]->rp->lessons[0]->grade << endl;

    return 0;
}