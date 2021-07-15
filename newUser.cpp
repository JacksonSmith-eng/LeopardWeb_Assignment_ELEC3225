#include "user.h"

// Function written by group
/////////////////////////////////////////////////////
// * * * * * * * * * * STUDENT * * * * * * * * * * //
/////////////////////////////////////////////////////
void newStudent(const char* dir, int& numStudent) {

	int userID, gradYear;
	std::string str, firstName, lastName, major;
	float GPA = 0.00;
	bool foundUID;

	do {
		std::cout << "\nPlease enter student's 4-digit user ID: ";
		std::cin >> userID;
		str = std::to_string(userID);
		std::cout << "\n";
		if (str.length() != 4)
			std::cout << "Please enter a valid user ID.\n";
		checkExistingUID(dir, userID, foundUID);
	} while (str.length() != 4);
	if (foundUID)
		std::cout << "This user already exists in the database.\n\n";
	else {
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
		numStudent++;
	}
}

// Function written by group
////////////////////////////////////////////////////////
// * * * * * * * * * * INSTRUCTOR * * * * * * * * * * //
////////////////////////////////////////////////////////
void newInstructor(const char* dir, int& numInstructor) {

	int userID;
	std::string str, firstName, lastName, title, department, degree;
	bool foundUID;

	do {
		std::cout << "Please enter instructor's 4-digit user ID: ";
		std::cin >> userID;
		std::cout << "\n";
		str = std::to_string(userID);
		if (str.length() != 4)
			std::cout << "Please enter a valid user ID.\n";
		checkExistingUID(dir, userID, foundUID);
	} while (str.length() != 4);
	if (foundUID)
			std::cout << "This user already exists in the database.\n";
	else {
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
	}
}

// Function written by group
///////////////////////////////////////////////////
// * * * * * * * * * * ADMIN * * * * * * * * * * //
///////////////////////////////////////////////////
void newAdmin(const char* dir, int& numAdmin) {

	int userID;
	std::string str, firstName, lastName, title, office;
	bool foundUID;

	do {
		std::cout << "\nPlease enter admin's 4-digit user ID: ";
		std::cin >> userID;
		std::cout << "\n";
		str = std::to_string(userID);
		if (str.length() != 4)
			std::cout << "Please enter a valid user ID.\n\n";
		checkExistingUID(dir, userID, foundUID);
	} while (str.length() != 4);
	if (foundUID)
			std::cout << "This user already exists in the database.\n";
	else {
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
	}
}