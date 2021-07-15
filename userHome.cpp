#include "user.h"

// Functions written by group

/////////////////////////////////////////////////////
// * * * * * * * * * * STUDENT * * * * * * * * * * //
/////////////////////////////////////////////////////
void studentHome(const char* dir, student_c* student) {

	int signedIn = 1;

	while (signedIn) {
		int choice = 6;

		std::cout << " * * * Student Home * * *\n";
		std::cout << "1: Search courses\n";
		std::cout << "2: Add/Drop courses\n";
		std::cout << "3: Display schedule\n";
		std::cout << "4: Display all student info\n";
		std::cout << "0: Sign out\n";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice) {
			case 1: { student->searchCourses(dir); break; }
			case 2: { student->addDropCourse(dir); break; }
			case 3: { student->printSchedule(dir); break; }
			case 4: { student->printAll(); break; }
			case 0: {
				do {
					if (signedIn != 0 && signedIn != 1)
						std::cout << "Please enter a valid choice.\n\n";
					std::cout << "You wish to sign out?\n";
					std::cout << "1: Stay signed in\n";
					std::cout << "0: Sign out\n";
					std::cin >> signedIn;
					std::cout << std::endl;
				} while (signedIn != 0 && signedIn != 1);
				break;
			}
			default: { std::cout << "Please enter a valid choice.\n\n"; }
		}
	}
}



////////////////////////////////////////////////////////
// * * * * * * * * * * INSTRUCTOR * * * * * * * * * * //
////////////////////////////////////////////////////////
void instructorHome(const char* dir, instructor_c* instructor) {

	std::ifstream inputStream;
	inputStream.open("The_Tests\\test_instructor_printCourseRoster\\test_instructor_HOME_printCourseRoster.txt");

	int signedIn = 1;

	while (signedIn) {
		int choice = 5;

		std::cout << " * * * Instructor Home * * *\n";
		std::cout << "1: Search courses\n";
		std::cout << "2: Display Course Roster\n";
		std::cout << "3: Display all instructor info\n";
		std::cout << "0: Sign out\n";
		//std::cin >> choice;
		inputStream >> choice;
		std::cout << std::endl;

		switch (choice) {
			case 1: { instructor->searchCourses(dir); break; }
			case 2: { instructor->printRosters(dir); break; }
			case 3: { instructor->printAll(); break; }
			case 0: {
				do {
					if (signedIn != 0 && signedIn != 1)
						std::cout << "Please enter a valid choice.\n\n";
					std::cout << "You wish to sign out?\n";
					std::cout << "1: Stay signed in\n";
					std::cout << "0: Sign out\n";
					//std::cin >> signedIn;
					inputStream >> signedIn;
					std::cout << std::endl;
				} while (signedIn != 0 && signedIn != 1);
				break;
			}
			default: { std::cout << "Please enter a valid choice.\n\n"; }
		}
	}
	inputStream.close();
}



///////////////////////////////////////////////////
// * * * * * * * * * * ADMIN * * * * * * * * * * //
///////////////////////////////////////////////////
void adminHome(const char* dir, const int& MAXSTUDENT, const int& MAXINSTRUCTOR, const int& MAXADMIN, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* admin, int& numStudent, int& numInstructor, int& numAdmin) {

	int signedIn = 1;

	while (signedIn) {
		int choice = 7;

		std::cout << " * * * Admin Home * * *\n";
		std::cout << "1: Add/Remove courses\n";
		std::cout << "2: Add/Remove users\n";
		std::cout << "3: Add/Drop students\n";
		std::cout << "4: Search for courses\n";
		std::cout << "5: Search for rosters\n";
		std::cout << "6: Display courses\n";
		std::cout << "7: Display all admin info\n";
		std::cout << "0: Sign out\n";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice) {
			case 1: { admin->addRemoveCourses(dir); break; }
			case 2: { admin->addRemoveUsers(dir, MAXSTUDENT, MAXINSTRUCTOR, MAXADMIN, signedInStudent, signedInInstructor, admin, numStudent, numInstructor, numAdmin); break; }
			case 3: { admin->addDropStudents(dir); break; }
			case 4: { admin->searchCourses(dir); break; }
			case 5: { admin->searchRosters(dir); break; }
			case 6: { admin->printCourses(dir); break; }
			case 7: { admin->printAll(); break; }
			case 0: {
				do {
					if (signedIn != 0 && signedIn != 1)
						std::cout << "Please enter a valid choice.\n\n";
					std::cout << "You wish to sign out?\n";
					std::cout << "1: Stay signed in\n";
					std::cout << "0: Sign out\n";
					std::cin >> signedIn;
					std::cout << std::endl;
				} while (signedIn != 0 && signedIn != 1);
				break;
			}
			default: { std::cout << "Please enter a valid choice.\n\n"; }
		}
	}
}