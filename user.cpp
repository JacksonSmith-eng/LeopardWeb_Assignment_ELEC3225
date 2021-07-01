#include "user.h"

//////////////////////////////////////////////////
// * * * * * * * * * * USER * * * * * * * * * * //
//////////////////////////////////////////////////
user_c::user_c(int ID, std::string firstName, std::string lastName) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
}

user_c::~user_c() { std::cout << "User "; std::cout << firstName << " " << lastName << " destructed\n"; }

void user_c::setAll(int ID, std::string firstName, std::string lastName) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
}
void user_c::setID(int) { this->ID = ID; }
void user_c::setFirstName(std::string) { this->firstName = firstName; }
void user_c::setLastName(std::string) { this->lastName = lastName; }

int user_c::getID() { std::cout << "User ID: " << ID << " searched\n"; return ID; }
std::string user_c::getFirstName() { return firstName; }
std::string user_c::getLastName() { return lastName; }

void user_c::printAll() {
	std::cout << "Name: " << firstName << " " << lastName << "\n";
	std::cout << "ID: " << ID << "\n";
}



/////////////////////////////////////////////////////
// * * * * * * * * * * STUDENT * * * * * * * * * * //
/////////////////////////////////////////////////////
student_c::student_c(int ID, std::string firstName, std::string lastName, std::string major, int gradYear, float GPA) : user_c(ID, firstName, lastName) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->major = major;
	this->gradYear = gradYear;
	this->GPA = GPA;
}
student_c::~student_c() { std::cout << "Student "; } // implement RNG

void student_c::setAll(int ID, std::string firstName, std::string lastName, std::string major, int gradYear, float GPA) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->major = major;
	this->gradYear = gradYear;
	this->GPA = GPA;
	user_c::setAll(ID, firstName, lastName);
}
void student_c::setMajor(std::string major) { this->major = major; }
void student_c::setGradYear(int) { this->gradYear = gradYear; }
void student_c::setGPA(float) { GPA = 0; }
std::string student_c::getMajor() { return major; }
int student_c::getGradYear() { return gradYear; }
float student_c::getGPA() { return GPA; }

void student_c::searchCourses() {
	std::cout << "Student search courses has been called.\n\n";
}

void student_c::addDropCourses() {
	std::cout << "Student add/drop courses has been called.\n\n";
}

void student_c::printSchedule() {
	std::cout << "Student print schedule has been called.\n\n";
}

void student_c::printGPA() {
	std::cout << "Student print GPA has been called.\n\n";
}

void student_c::printAll() {
	std::cout << " * * * Student Info * * * \n";
	user_c::printAll();
	std::cout << "GPA: " << GPA << "\n\n";
}



////////////////////////////////////////////////////////
// * * * * * * * * * * INSTRUCTOR * * * * * * * * * * //
////////////////////////////////////////////////////////
instructor_c::instructor_c(int ID, std::string firstName, std::string lastName, std::string title, std::string department, std::string degree) : user_c(ID, firstName, lastName) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->title = title;
	this->department = department;
	this->degree = degree;
}
instructor_c::~instructor_c() { std::cout << "Instructor "; }

void instructor_c::setAll(int ID, std::string firstName, std::string lastName, std::string title, std::string department, std::string degree) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->title = title;
	this->department = department;
	this->degree = degree;
	user_c::setAll(ID, firstName, lastName);
}
void instructor_c::setTitle(std::string title) { this->title = title; }
void instructor_c::setDepartment(std::string department) { this->department = department; }
void instructor_c::setDegree(std::string degree) { this->degree = degree; }

std::string instructor_c::getTitle() { return title; }
std::string instructor_c::getDepartment() { return department; }
std::string instructor_c::getDegree() { return degree; }

void instructor_c::searchCourses() {
	std::cout << "Instructor search has been called.\n\n";
}

void instructor_c::printSchedule() {
	std::cout << "Instructor print schedule has been called.\n\n";
}

void instructor_c::printClasslist() {
	std::cout << "Instructor print classlist has been called.\n\n";
}

void instructor_c::printAll() {
	std::cout << " * * * Instructor Info * * * \n";
	user_c::printAll();
	std::cout << "Degree: " << degree << "\n";
	std::cout << "Department: " << department << "\n\n";
}



///////////////////////////////////////////////////
// * * * * * * * * * * ADMIN * * * * * * * * * * //
///////////////////////////////////////////////////
admin_c::admin_c(int ID, std::string firstName, std::string lastName, std::string title, std::string office) : user_c(ID, firstName, lastName) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->title = title;
	this->office = office;
}
admin_c::~admin_c() { std::cout << "Admin "; }

void admin_c::setAll(int ID, std::string firstName, std::string lastName, std::string title, std::string office) {
	this->ID = ID;
	this->firstName = firstName;
	this->lastName = lastName;
	this->title = title;
	this->office = office;
	user_c::setAll(ID, firstName, lastName);
}
void admin_c::setTitle(std::string title) { this->title = title; }
void admin_c::setOffice(std::string office) { this->office = office; }
std::string admin_c::getTitle() { return title; }
std::string admin_c::getOffice() { return office; }

void admin_c::addRemoveCourses() {
	std::cout << "Admin add/drop courses has been called.\n\n";
}

void admin_c::addRemoveUsers(const char* dir, const int& MAXSTUDENT, const int& MAXINSTRUCTOR, const int& MAXADMIN, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* signedInAdmin, int& numStudent, int& numInstructor, int& numAdmin) {
	
	int userType = 0;
	std::cout << "Creating new accout.\nEnter account information:\n";
	std::cout << "1: Student\n";
	std::cout << "2: Instructor\n";
	std::cout << "3: Admin\n";
	std::cin >> userType;

	switch (userType) {
		case 1: { // Create new student
			if (numStudent >= MAXSTUDENT) {
				std::cout << "\nSorry, our student database is currently at its maximum.\n\n";
				userType = 0;
			}
			else {
				newStudent(dir);
				numStudent++;
			}
			break;
		}
		case 2: { // Create new instructor
			if (numInstructor >= MAXINSTRUCTOR) {
				std::cout << "\nSorry, our instructor database is currently at its maximum.\n\n";
				userType = 0;
			}
			else {
				newInstructor(dir);
				numInstructor++;
			}
			break;
		}
		case 3: { // Create new admin
			if (numAdmin >= MAXADMIN) {
				std::cout << "\nSorry, our admin database is currently at its maximum.\n\n";
				userType = 0;
			}
			else {
				newAdmin(dir);
				numAdmin++;
			}
			break;
		}
		default: { std::cout << "Please enter a valid input.\n"; }
	}
}

void admin_c::addDropStudents() {
	std::cout << "Admin add/drop students has been called.\n\n";
}

void admin_c::searchCourses() {
	std::cout << "Admin search courses has been called.\n\n";
}

void admin_c::searchRosters() {
	std::cout << "Admin search rosters has been called.\n\n";
}

void admin_c::printCourses() {
	std::cout << "Admin print courses has been called.\n\n";
}

void admin_c::printRoster() {
	std::cout << "Admin print roster has been called.\n\n";
}

void admin_c::printAll() {
	std::cout << " * * * Admin Info * * * \n";
	user_c::printAll();
	std::cout << "\n\n";
}



////////////////////////////////////////////////////
// * * * * * * * * * * COURSE * * * * * * * * * * //
////////////////////////////////////////////////////
course_c::course_c(int courseID, std::string courseName, std::string departmnent, int credits, std::string time, std::string daysOfWeek, std::string semester, int year) {
	this->courseID = courseID;
	this->courseName = courseName;
	this->department = department;
	this->credits = credits;
	this->time = time;
	this->daysOfWeek = daysOfWeek;
	this->semester = semester;
	this->year = year;
}
course_c::~course_c() { std::cout << "Course " << courseName << " destructed\n"; };

void course_c::setCourseID(int) { this->courseID = courseID; };
void course_c::setCourseName(std::string) { this->courseName = courseName; };
void course_c::setDepartment(std::string) { this->department = department; };
void course_c::setCredits(int) { this->credits = credits; };
void course_c::setTime(std::string) { this->time = time; };
void course_c::setDaysOfWeek(std::string) { this->daysOfWeek = daysOfWeek; };
void course_c::setSemester(std::string) { this->semester = semester; };
void course_c::setYear(int) { this->year = year; };

int course_c::getCourseID() { return courseID; };
std::string course_c::getCourseName() { return courseName; };
std::string course_c::getDepartment() { return department; };
int course_c::getCredits() { return credits; };
std::string course_c::getTime() { return time; };
std::string course_c::getDaysOfWeek() { return daysOfWeek; };
std::string course_c::getSemester() { return semester; };
int course_c::getYear() { return year; };