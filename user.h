#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

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

		void searchCourses();
		void addDropCourses();
		void printSchedule();
		void printGPA();

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

		void searchCourses();
		void printSchedule();
		void printClasslist();

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

		void addRemoveCourses();
		void addRemoveUsers(const char*, const int&, const int&, const int&, student_c*, instructor_c*, admin_c*, int&, int&, int&);
		void addDropStudents();
		void searchCourses();
		void searchRosters();
		void printCourses();
		void printRoster();

		void printAll();
};



////////////////////////////////////////////////////
// * * * * * * * * * * COURSE * * * * * * * * * * //
////////////////////////////////////////////////////
class course_c {
	private:
		int courseID, year, credits;
		std::string courseName, department, daysOfWeek, time, semester;
		//std::vector vector that holds all studdents in course

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

		int getCourseID();
		std::string getCourseName();
		std::string getDepartment();
		int getCredits();
		std::string getTime();
		std::string getDaysOfWeek();
		std::string getSemester();
		int getYear();
};



extern int createDB(const char*);
extern int createTable(const char*, std::string); // Student, instructor, admin
extern int clearTable(const char*, std::string); // Student, instructor, admin
extern int loadInData(const char*, int&, int&, int&);
extern int insertUser(const char*, int, std::string, std::string, std::string, int, float); // Student
extern int insertUser(const char*, int, std::string, std::string, std::string, std::string, std::string); // Instructor
extern int insertUser(const char*, int, std::string, std::string, std::string, std::string); // Admin
extern int signInUser(const char* s, int userID, int& userType, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* signedInAdmin);
extern int updateData(const char*);
extern int printTable(const char*, std::string); // Student, instructor, admin
extern int callback_print(void*, int, char**, char**);
extern int callback_newUser(void*, int, char**, char**);

void newStudent(const char* s);
void newInstructor(const char* s);
void newAdmin(const char* s);

void deleteAllStudents(std::list<student_c*> studentUsers);
void deleteAllInstructors(std::list<instructor_c*> instructorUsers);
void deleteAllAdmin(std::list<admin_c*> adminUsers);

void studentHome(student_c* student);
void instructorHome(instructor_c* instructor);
void adminHome(const char*, const int&, const int&, const int&, student_c*, instructor_c*, admin_c*, int&, int&, int&);

#endif