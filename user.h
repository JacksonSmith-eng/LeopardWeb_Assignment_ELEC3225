#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

// Classes written by group

//////////////////////////////////////////////////
// * * * * * * * * * * USER * * * * * * * * * * //
//////////////////////////////////////////////////
class user_c {
	protected:
		int ID;
		std::string firstName, lastName;

	public:
		user_c(int, std::string, std::string);
		~user_c();

		void setAll(int, std::string, std::string);
		void setID(int);
		void setFirstName(std::string);
		void setLastName(std::string);
		
		int getID();
		std::string getFirstName();
		std::string getLastName();

		void printAll();
};



/////////////////////////////////////////////////////
// * * * * * * * * * * STUDENT * * * * * * * * * * //
/////////////////////////////////////////////////////
class student_c : public user_c {
	private:
		std::string major;
		int gradYear;
		float GPA;

	public:
		student_c(int, std::string, std::string, std::string, int, float);
		~student_c();

		void setAll(int, std::string, std::string, std::string, int, float);
		void setMajor(std::string);
		void setGradYear(int);
		void setGPA(float);
		std::string getMajor();
		int getGradYear();
		float getGPA();

		void searchCourses(const char*);
		void addDropCourse(const char*);
		void printSchedule(const char*);

		void printAll();
};



////////////////////////////////////////////////////////
// * * * * * * * * * * INSTRUCTOR * * * * * * * * * * //
////////////////////////////////////////////////////////
class instructor_c : public user_c {
	private:
		std::string title, department, degree;

	public:
		instructor_c(int, std::string, std::string, std::string, std::string, std::string);
		~instructor_c();

		void setAll(int, std::string, std::string, std::string, std::string, std::string);
		void setTitle(std::string);
		void setDepartment(std::string);
		void setDegree(std::string);
		std::string getTitle();
		std::string getDepartment();
		std::string getDegree();

		void searchCourses(const char*);
		void printRosters(const char*);

		void printAll();
};



///////////////////////////////////////////////////
// * * * * * * * * * * ADMIN * * * * * * * * * * //
///////////////////////////////////////////////////
class admin_c : public user_c {
	private:
		std::string title, office;

	public:
		admin_c(int, std::string, std::string, std::string, std::string);
		~admin_c();

		void setAll(int, std::string, std::string, std::string, std::string);
		void setTitle(std::string);
		void setOffice(std::string);
		std::string getTitle();
		std::string getOffice();

		void searchCourses(); // Same for all
		void addDropStudents(); // Same as in student_c
		void addRemoveCourses();
		void addRemoveUsers(const char*, const int&, const int&, const int&, student_c*, instructor_c*, admin_c*, int&, int&, int&);
		void printRosters(); // Same as in inctructor_c
		void printCourses();

		void printAll();
};



////////////////////////////////////////////////////
// * * * * * * * * * * COURSE * * * * * * * * * * //
////////////////////////////////////////////////////
class course_c {
	private:
		int courseID, year, credits;
		std::string courseName, department, daysOfWeek, time, semester;
		//int instructor;
		//std::vector<int> enrolledStudents;

	public:
		course_c(int courseID, std::string courseName, std::string department, int credits, std::string time, std::string daysOfWeek, std::string semester, int year);
		~course_c();

		void setCourseID(int);
		void setCourseName(std::string);
		void setDepartment(std::string);
		void setCredits(int);
		void setTime(std::string);
		void setDaysOfWeek(std::string);
		void setSemester(std::string);
		void setYear(int);
		//void setInstructor(int);

		int getCourseID();
		std::string getCourseName();
		std::string getDepartment();
		int getCredits();
		std::string getTime();
		std::string getDaysOfWeek();
		std::string getSemester();
		int getYear();
		//int getInstructor();
};



extern int createDB(const char*);
extern int createTable(const char*, std::string); // Student, instructor, admin
extern int clearTable(const char*, std::string); // Student, instructor, admin
extern int loadInData(const char*, int&, int&, int&);
extern int insertUser(const char*, int, std::string, std::string, std::string, int, float); // Student
extern int insertUser(const char*, int, std::string, std::string, std::string, std::string, std::string); // Instructor
extern int insertUser(const char*, int, std::string, std::string, std::string, std::string); // Admin
extern int signInUser(const char* s, int userID, int& userType, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* signedInAdmin);
extern int addStudent(const char*, int, int);
extern int dropStudent(const char*, int, int);
extern int updateData(const char*);
extern int printTable(const char*, std::string); // Student, instructor, admin
extern int printCourse(const char*, int);
extern int printRoster(const char*, int);
extern int callback_printData(void*, int, char**, char**);
extern int callback_getData(void*, int, char**, char**);

void newStudent(const char* s);
void newInstructor(const char* s);
void newAdmin(const char* s);

void studentHome(const char*, student_c* student);
void instructorHome(const char*, instructor_c* instructor);
void adminHome(const char*, const int&, const int&, const int&, student_c*, instructor_c*, admin_c*, int&, int&, int&);

#endif