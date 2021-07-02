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

void student_c::searchCourses(const char* dir) { /* https://www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++ */

	int choice = 3;

	while (choice) {
		std::cout << " * * * Course Search * * * \n";
		std::cout << "1: Search courses by CID\n";
		std::cout << "2: Show all courses\n";
		std::cout << "0: Return to Home\n";
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1: {
			std::vector<std::string> courseID;
			std::string input;

			int invalid = 0;

			do {
				invalid = 0;
				std::cin.ignore();
				std::cout << "Please enter the 4-digit course IDs separated by spaces: ";
				getline(std::cin, input);
				std::cout << "\n";

				std::istringstream iss(input);
				for (std::string input; iss >> input; )
					courseID.push_back(input);

				for (int i = 0; i < courseID.size(); i++) {
					if (courseID[i].length() != 4) {
						invalid = 1;
						break;
					}
				}
				if (invalid) {
					std::cout << "\nPlease enter valid course IDs.\n\n";
					for (int i = 0; i <= courseID.size(); i++)
						courseID.pop_back();
				}
			} while (invalid);

			std::cout << "\n";

			for (int i = 0; i < courseID.size(); i++)
				printCourse(dir, std::stoi(courseID[i]));
			break;
		}
		case 2: {
			printTable(dir, "COURSE");
			break;
		}
		case 0:
			break;
		default: {
			std::cout << "\nPlease enter a valid choice.\n\n";
		}
		}
	}
}

void student_c::addDropCourse(const char* dir) {

	int choice = 5, courseID = 0;
	std::string str;

	while (choice) {
		std::cout << " * * * Add/Drop Course * * * \n";
		std::cout << "1: Search courses\n";
		std::cout << "2: Display schedule\n";
		std::cout << "3: Add a course\n";
		std::cout << "4: Drop a course\n";
		std::cout << "0: Return to Home\n";
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1: {
			searchCourses(dir);
			break;
		}
		case 2: {
			printRoster(dir, ID);
			break;
		}
		case 3: {
			do {
				std::cout << "Please enter the 4-digit course ID: ";
				std::cin >> courseID;
				std::cout << "\n";
				str = std::to_string(courseID);
				if (str.length() != 4)
					std::cout << "Please enter a valid user ID.\n\n";
			} while (str.length() != 4);

			addStudent(dir, ID, courseID);

			break;
		}
		case 4: {
			do {
				std::cout << "Please enter the 4-digit course ID: ";
				std::cin >> courseID;
				std::cout << "\n";
				str = std::to_string(courseID);
				if (str.length() != 4)
					std::cout << "Please enter a valid user ID.\n\n";
			} while (str.length() != 4);

			dropStudent(dir, ID, courseID);

			break;
		}
		case 0:
			break;
		default: {
			std::cout << "\nPlease enter valid choice.\n\n";
		}
		}
	}
}

void student_c::printSchedule(const char* dir) {
	printRoster(dir, ID);
}

void student_c::printAll() {
	std::cout << " * * * Student Info * * * \n";
	user_c::printAll();
	std::cout << "Major: " << major << "\n";
	std::cout << "Graduation Year: " << gradYear << "\n";
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

void instructor_c::printRosters() {
	std::cout << "Instructor search rosters has been called.\n\n";
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

void admin_c::addRemoveCourses(const char* dir) {

	int choice = 3, courseID = 0;
	std::string str;

	while (choice) {
		std::cout << " * * * Add/Drop Course * * * \n";
		std::cout << "1: Add a course\n";
		std::cout << "2: Drop a course\n";
		std::cout << "0: Return to Home\n";
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1: {
			do {
				std::cout << "Please enter the 4-digit course ID: ";
				std::cin >> courseID;
				std::cout << "\n";
			} while (str.length() != 4);

			addCourse(dir,courseID);

			break;
		}
		case 2: {
			do {
				std::cout << "Please enter the 4-digit course ID: ";
				std::cin >> courseID;
				std::cout << "\n";
			} while (str.length() != 4);

			dropCourse(dir, courseID);

			break;
		}
		case 0:
			break;
		default: {
			std::cout << "\nPlease enter valid choice.\n\n";
		}
		}
	}
}

void admin_c::addRemoveUsers(const char* dir, const int& MAXSTUDENT, const int& MAXINSTRUCTOR, const int& MAXADMIN, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* signedInAdmin, int& numStudent, int& numInstructor, int& numAdmin) {

	int userType = 0, choice = 4;

	while (choice) {

		std::cout << " * * * Add/Drop User * * *\n";
		std::cout << "Search for a user: \n";
		std::cout << "2: Add a user: \n";
		std::cout << "3: Drop a user: \n";
		std::cin >> choice;
		std::cout << "\n";
		switch (choice) {
		case 1: {
			// * * * MUST BE IMPLEMENTED * * *
		}
		case 2: {
			std::cout << "Enter account information: \n";
			std::cout << "1: Student\n";
			std::cout << "2: Instructor\n";
			std::cout << "3: Admin\n";
			std::cin >> userType;
			std::cout << "\n";

			switch (userType) {
			case 1: {
				if (numStudent >= MAXSTUDENT) {
					std::cout << "Sorry, our student database is currently at its maximum.\n\n";
					userType = 0;
				}
				else {
					newStudent(dir);
					numStudent++;
				}
				break;
			}
			case 2: {
				if (numInstructor >= MAXINSTRUCTOR) {
					std::cout << "Sorry, our instructor database is currently at its maximum.\n\n";
					userType = 0;
				}
				else {
					newInstructor(dir);
					numInstructor++;
				}
				break;
			}
			case 3: {
				if (numAdmin >= MAXADMIN) {
					std::cout << "Sorry, our admin database is currently at its maximum.\n\n";
					userType = 0;
				}
				else {
					newAdmin(dir);
					numAdmin++;
				}
				break;
			}
			default:
				std::cout << "Please enter a valid input.\n";
			}
		}
		case 3: {
			// * * * MUST BE IMPLEMENTED * * *
		}
		default:
			std::cout << "Please enter a valid input.\n";
		}
	}
}

void admin_c::addDropStudents(const char* dir) {

	int choice = 5, courseID = 0;
	std::string str;

	while (choice) {
		std::cout << " * * * Add/Drop Student * * * \n";
		std::cout << "1: Add a Student\n";
		std::cout << "2: Drop a Student\n";
		std::cout << "0: Return to Home\n";
		std::cin >> choice;
		std::cout << "\n";

		switch (choice) {
		case 1: {
			do {
				std::cout << "Please enter the 4-digit course ID: ";
				std::cin >> ID;
				std::cout << "\n";
				str = std::to_string(courseID);
				if (str.length() != 4)
					std::cout << "Please enter a valid user ID.\n\n";
			} while (str.length() != 4);

			addStudent(dir, ID, courseID);

			break;
		}
		case 2: {
			do {
				std::cout << "Please enter the 4-digit Student ID: ";
				std::cin >> ID;
				std::cout << "\n";
				std::cout << "Please enter the 4-digit course ID: ";
				std::cin >> courseID;
				std::cout << "\n";
				str = std::to_string(courseID);
				if (str.length() != 4)
					std::cout << "Please enter a valid user ID.\n\n";
			} while (str.length() != 4);

			dropStudent(dir, ID, courseID);

			break;
		}
		case 0:
			break;
		default: {
			std::cout << "\nPlease enter valid choice.\n\n";
		}
		}
	}
}

void admin_c::searchCourses(const char* dir) {
	searchCourses(dir);
}

void admin_c::printCourses(const char* dir) {
	printTable(dir, "COURSE");
}

void admin_c::printRosters(const char* dir) {
	printRoster(dir, ID);
}

void admin_c::printAll() {
	std::cout << " * * Admin Info * * * \n";
	user_c::printAll();
	std::cout << "Title: " << title << "\n";
	std::cout << "Office: " << office << "\n";
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

void course_c::setCourseID(int courseID) { this->courseID = courseID; };
void course_c::setCourseName(std::string courseName) { this->courseName = courseName; };
void course_c::setDepartment(std::string department) { this->department = department; };
void course_c::setCredits(int credits) { this->credits = credits; };
void course_c::setTime(std::string time) { this->time = time; };
void course_c::setDaysOfWeek(std::string daysOfWeek) { this->daysOfWeek = daysOfWeek; };
void course_c::setSemester(std::string semester) { this->semester = semester; };
void course_c::setYear(int year) { this->year = year; };
//void course_c::setInstructor(int instructor) { this->instructor = instructor; }

int course_c::getCourseID() { return courseID; };
std::string course_c::getCourseName() { return courseName; };
std::string course_c::getDepartment() { return department; };
int course_c::getCredits() { return credits; };
std::string course_c::getTime() { return time; };
std::string course_c::getDaysOfWeek() { return daysOfWeek; };
std::string course_c::getSemester() { return semester; };
int course_c::getYear() { return year; };
//int course_c::getInstructor() { return instructor; }