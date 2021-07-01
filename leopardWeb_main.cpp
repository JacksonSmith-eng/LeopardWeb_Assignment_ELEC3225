/*
When program begins, some hardcoded users should populate db
When program ends, delete everything

Replace all instances of the std::list with SQL
 - deleteUser.cpp: complete redo
 - newUser.cpp: list is passed as argument, change to DB
 - user.cpp: add to functions

Create table for courses w/ enrolled students

 Separate userDB and courseDB
 */

#include "user.h"

int main() {
	/*********************************************************/
	const int MAXSTUDENT = 100;
	const int MAXINSTRUCTOR = 10;
	const int MAXADMIN = 1;
	/*********************************************************/
	
	const char* dir = "C:\\Users\\smithj42\\Documents\\2020-2021\\Applied_Programming_Concepts\\Semester_Assignment\\LeopardWeb_Assignment\\LeopardWeb_Assignment_ELEC3225\\The_Database\\leopardWeb.db";
	sqlite3* DB;
	
	int userID;
	int userType = 0, numStudent = 0, numInstructor = 0, numAdmin = 0, run_program = 1;

	student_c* signedInStudent = new student_c(0000, "NULL", "NULL", "NULL", 0, 0.00);
	instructor_c* signedInInstructor = new instructor_c(0000, "NULL", "NULL", "NULL", "NULL", "NULL");
	admin_c* signedInAdmin = new admin_c(0000, "NULL", "NULL", "NULL", "NULL");

	createDB(dir);
	// Comment out when program is implemented: BEGIN
	createTable(dir, "STUDENT");
	createTable(dir, "INSTRUCTOR");
	createTable(dir, "ADMIN");
	createTable(dir, "COURSE");

	clearTable(dir, "STUDENT");
	clearTable(dir, "INSTRUCTOR");
	clearTable(dir, "ADMIN");
	clearTable(dir, "COURSE");

	loadInData(dir, numStudent, numInstructor, numAdmin);

	printTable(dir, "STUDENT");
	printTable(dir, "INSTRUCTOR");
	printTable(dir, "ADMIN");
	printTable(dir, "COURSE");
	// Comment out when program is implemented: END
	while (run_program) {
		userType = 0;
		std::cout << " * * * LeopardWeb * * *\n"; // Homepage	
		//std::cout << "2: Create account\n";
		std::cout << "1: Sign in\n";
		std::cout << "0: End program\n";
		std::cin >> run_program;
		std::cout << std::endl;
		switch (run_program) {
			case 1: { // Sign into account
				std::string str;
				do {
					std::cout << "Please enter your 4-digit user ID: ";
					std::cin >> userID;
					std::cout << "\n";
					str = std::to_string(userID);
					if (str.length() != 4)
						std::cout << "Please enter a valid user ID.\n\n";
				} while (str.length() != 4);
				if ((numStudent == 0) & (numInstructor == 0) & (numAdmin == 0))
					std::cout << "Sorry, the database is empty\n\n";
				else {
					std::cout << "MAIN: sign in user\n";
					signInUser(dir, userID, userType, signedInStudent, signedInInstructor, signedInAdmin);

					if (!userType) {
						std::cout << "Sorry, we couldn't find you in the database.\n";
					}
					std::cout << "\n";
				}
				break;
			}
			case 0: { // Exit program
				userType = 0;
				do {
					if (run_program != 0 && run_program != 1)
						std::cout << "Please enter a valid input.\n\n";
					std::cout << "You wish to exit?\n";
					std::cout << "1: Return\n";
					std::cout << "0: Exit\n";
					std::cin >> run_program;
					std::cout << std::endl;
				} while (run_program != 0 && run_program != 1);
				break;
			}
			default: { std::cout << "Please enter a valid input.\n\n"; }
		}
			/*********************************************************/
		if (run_program) {
			switch (userType) { // Go to user home
				case 1: { studentHome(signedInStudent); break; }
				case 2: { instructorHome(signedInInstructor); break; }
				case 3: { adminHome(dir, MAXSTUDENT, MAXINSTRUCTOR, MAXADMIN, signedInStudent, signedInInstructor, signedInAdmin, numStudent, numInstructor, numAdmin); break; }
				case 0: { break; }
				default: { std::cout << "Please enter a valid input.\n"; }
			}
		}
	}
	/*********************************************************/
	std::cout << " * * * EXITING * * * \n";
	// Comment out when program is implemented: BEGIN
	printTable(dir, "STUDENT");
	printTable(dir, "INSTRUCTOR");
	printTable(dir, "ADMIN");
	printTable(dir, "COURSE");
	// Comment out when program is implemented: END
	//delete signedInStudent;
	//delete signedInInstructor;
	//delete signedInAdmin;

	std::cout << "\n";

	return 0;
}