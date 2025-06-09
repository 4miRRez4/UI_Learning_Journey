#include <iostream>
class Student{
	public:
		Student() {name="default", age=0, studentNumber=0;}
		Student(std::string n, int a, int sn) { name=n, age=a, studentNumber=sn;}
		void setName(std::string n) { name=n;}
		void setAge(int a) { age=a;}
		void setStudentNumber(int sn) { studentNumber=sn;}
		std::string getName() {return name;}
		int getAge() {return age;}
		int getStudentNumber() {return studentNumber;}
	private:
		int age;
		std::string name;
		int studentNumber;
};
std::string getOldestName(Student arr[5]){
	Student oldest = arr[0];
	for(int i=1; i<5; i++)
		if(arr[i].getAge() > oldest.getAge())
			oldest = arr[i];
	return oldest.getName();
}
int main(){
	Student arr[5];
	arr[0] = Student("amir",18,402);
	arr[1] = Student("reza",19,401);
	arr[2] = Student("mohammad",15,405);
	arr[3] = Student("ali",14,406);
	arr[4] = Student("mehdi",10,410);
	std::cout << "oldest student: " << getOldestName(arr) << std::endl;
	//if we wanted to declare array as pointer to students. in initialization we should have done something line this:
	//Student s=Student("amir",18,402);
	//arr[0] = &s;
	//and so on. after that we must have changed input parameter of getOldestName function to => Student* arr[5].
	//and instead of using dot(.) for accessing object features, we should have use this(->). like => arr[i]->getAge().
	return 0;}

