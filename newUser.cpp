#include "user.h"

// Function written by group
/////////////////////////////////////////////////////
// * * * * * * * * * * STUDENT * * * * * * * * * * //
/////////////////////////////////////////////////////
void newStudent(const char* dir) {

	int userID, gradYear;
	std::string str, firstName, lastName, major;
	float GPA = 0.00;

	do {
		std::cout << "\nPlease enter student's 4-digit user ID: ";
		std::cin >> userID;
		str = std::to_string(userID);
		std::cout << "\n";
		if (str.length() != 4)
			std::cout << "Please enter a valid user ID.\n\n";
		/*for (it = studentUsers.begin(); it != studentUsers.end(); it++) {
			if ((*it)->getID() == userID) {
				std::cout << "\nThis user ID has already been taken.\nPlease enter another.\n\n";
				break;
			}
		}*/
	} while (str.length() != 4/* || (*it)->getID() == userID*/) ;
	std::cout << "Please enter student's first name: ";
	std::cin >> firstName;
	std::cout << "Please enter student's last name: ";
	std::cin >> lastName;
	std::cout << "Please enter student's major: ";
	std::cin >> major;
	std::cout << "Please enter student's year of graduation: ";
	std::cin >> gradYear;
	std::cout << "\n";

	insertUser(dir, userID, firstName, lastName, major, gradYear, GPA);

	//return new student_c(userID, firstName, lastName, major, gradYear, 0.00);
}

// Function written by group
////////////////////////////////////////////////////////
// * * * * * * * * * * INSTRUCTOR * * * * * * * * * * //
////////////////////////////////////////////////////////
void newInstructor(const char* dir) {

	int userID;
	std::string str, firstName, lastName, title, department, degree;

	do {
		std::cout << "Please enter instructor's 4-digit user ID: ";
		std::cin >> userID;
		std::cout << "\n";
		str = std::to_string(userID);
		if (str.length() != 4) {
			std::cout << "Please enter a valid user ID.\n\n";
		}/*
		it = instructorUsers.begin();
		for (std::list<instructor_c*>::iterator it = instructorUsers.begin(); it != instructorUsers.end(); it++) {
			if ((*it)->getID() == userID) {
				std::cout << "\nThis user ID has already been taken.\nPlease enter another.\n\n";
				break;
			}
		}*/
	} while (str.length() != 4/* || (*it)->getID() == userID*/);
	std::cout << "Please enter instructor's first name: ";
	std::cin >> firstName;
	std::cout << "Please enter instructor's last name: ";
	std::cin >> lastName;
	std::cout << "Please enter instructor's title: ";
	std::cin >> title;
	std::cout << "Please enter instructor's department: ";
	std::cin >> department;
	std::cout << "Please enter instructor's highest earned degree: ";
	std::cin >> degree;
	std::cout << "\n";

	insertUser(dir, userID, firstName, lastName, title, department, degree);

	//return new instructor_c(userID, firstName, lastName, title, department, degree);
}

// Function written by group
///////////////////////////////////////////////////
// * * * * * * * * * * ADMIN * * * * * * * * * * //
///////////////////////////////////////////////////
void newAdmin(const char* dir) {

	int userID;
	std::string str, firstName, lastName, title, office;

	do {
		std::cout << "\nPlease enter admin's 4-digit user ID: ";
		std::cin >> userID;
		std::cout << "\n";
		str = std::to_string(userID);
		if (str.length() != 4)
			std::cout << "Please enter a valid user ID.\n\n";
		/*it = adminUsers.begin();
		for (it = adminUsers.begin(); it != adminUsers.end(); it++) {
			if ((*it)->getID() == userID) {
				std::cout << "\nThis user ID has already been taken.\nPlease enter another.\n\n";
				break;
			}
		}*/
	} while (str.length() != 4/* || (*it)->getID() == userID*/);
	std::cout << "Please enter admin's first name: ";
	std::cin >> firstName;
	std::cout << "Please enter admin's last name: ";
	std::cin >> lastName;
	std::cout << "Please enter admin's title: ";
	std::cin >> firstName;
	std::cout << "Please enter admin's office: ";
	std::cin >> lastName;
	std::cout << "\n";

	insertUser(dir, userID, firstName, lastName, title, office);

	//return new admin_c(userID, firstName, lastName, title, office);
}
