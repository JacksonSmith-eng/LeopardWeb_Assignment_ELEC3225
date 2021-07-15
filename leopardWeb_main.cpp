/*
For testing:
 - When program begins, some hardcoded users should populate db
 - When program ends, delete everything

Functions that need to check if user/course is already in DB:
 - admin_c::addRemoveCourses()
 - admin_c::addRemoveUsers()
 - student_c::addDropCourse()
 */ 

#include "user.h"
#include <fstream>

 // Main function written by group
int main() {
	/*********************************************************/
	const int MAXSTUDENT = 100;
	const int MAXINSTRUCTOR = 10;
	const int MAXADMIN = 1;
	/*********************************************************/

	std::ifstream inputStream;
	inputStream.open("C:\\Users\\pasquelr\\Desktop\\LeopardWebAssignment\\The_Tests\\TestUserSignInOut\\Test_userMain_signInOut.txt");
	//inputStream.open("The_Tests\\test_admin_showInfo.txt");

	std::ofstream outputStream;

	const char* dir = "C:\\Users\\pasquelr\\Desktop\\LeopardWebAssignment\\leopardWeb.db";
	sqlite3* DB;

	int userID;
	int userType = 0, numStudent = 0, numInstructor = 0, numAdmin = 0, run_program = 1;

	student_c* signedInStudent = new student_c(0000, "NULL", "NULL", "NULL", 0, 0.00);
	instructor_c* signedInInstructor = new instructor_c(0000, "NULL", "NULL", "NULL", "NULL", "NULL");
	admin_c* signedInAdmin = new admin_c(0000, "NULL", "NULL", "NULL", "NULL");

	createDB(dir);
	// Comment out when program is implemented: BEGIN
	/*createTable(dir, "STUDENT");
	createTable(dir, "INSTRUCTOR");
	createTable(dir, "ADMIN");
	createTable(dir, "COURSE");
	createTable(dir, "ROSTER");
	*/
	clearTable(dir, "STUDENT");
	clearTable(dir, "INSTRUCTOR");
	clearTable(dir, "ADMIN");
	clearTable(dir, "COURSE");
	clearTable(dir, "ROSTER");

	loadInData(dir, numStudent, numInstructor, numAdmin);
	/*
	printTable(dir, "STUDENT");
	printTable(dir, "INSTRUCTOR");
	printTable(dir, "ADMIN");
	printTable(dir, "COURSE");
	printTable(dir, "ROSTER");*/
	// Comment out when program is implemented: END
	while (run_program) {
		userType = 0;
		std::cout << " * * * LeopardWeb * * *\n"; // Homepage	
		std::cout << "1: Sign in\n";
		std::cout << "0: End program\n";
		//std::cin >> run_program;
		inputStream >> run_program;
		std::cout << "\n";
		switch (run_program) {
		case 1: { // Sign into account
			std::string str;
			do {
				std::cout << "Please enter your 4-digit user ID: ";
				//std::cin >> userID;
				inputStream >> userID;
				std::cout << "\n";
				str = std::to_string(userID);
				if (str.length() != 4)
					std::cout << "Please enter a valid user ID.\n\n";
			} while (str.length() != 4);
			if ((numStudent == 0) & (numInstructor == 0) & (numAdmin == 0))
				std::cout << "Sorry, the database is empty\n\n";
			else {
				signInUser(dir, userID, userType, signedInStudent, signedInInstructor, signedInAdmin);

				if (!userType) {
					std::cout << "Sorry, we couldn't find you in the database.\n";
				}
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
				//std::cin >> run_program;
				inputStream >> run_program;
				std::cout << std::endl;
			} while (run_program != 0 && run_program != 1);
			break;
		}
		default: { std::cout << "Please enter a valid choice.\n\n"; }
		}
		/*********************************************************/
		if (run_program) {
			switch (userType) { // Go to user home
			case 1: { studentHome(dir, signedInStudent); break; }
			case 2: { instructorHome(dir, signedInInstructor); break; }
			case 3: { adminHome(dir, MAXSTUDENT, MAXINSTRUCTOR, MAXADMIN, signedInStudent, signedInInstructor, signedInAdmin, numStudent, numInstructor, numAdmin); break; }
			case 0: { break; }
			default: { std::cout << "Please enter a valid choice.\n"; }
			}
		}
	}
	/*********************************************************/
	std::cout << " * * * EXITING * * * \n";
	// Comment out when program is implemented: BEGIN
	/*printTable(dir, "STUDENT");
	printTable(dir, "INSTRUCTOR");
	printTable(dir, "ADMIN");
	printTable(dir, "COURSE");
	printTable(dir, "ROSTER");*/
	// Comment out when program is implemented: END

	inputStream.close();

	return 0;
}
