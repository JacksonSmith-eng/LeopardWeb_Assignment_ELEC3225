#include "user.h"

// Function written by group
extern int createDB(const char* s) {
	
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

// Function written by group
extern int createTable(const char* s, std::string tableType) {
	
	sqlite3* DB;
	std::string table;

	if (tableType == "STUDENT") {
		table = "CREATE TABLE STUDENT("
			"SID INTEGER PRIMARY KEY, "
			"NAME TEXT NOT NULL, "
			"SURNAME TEXT NOT NULL, "
			"MAJOR TEXT NOT NULL, "
			"GRADYEAR INTEGER NOT NULL,"
			"GPA FLOAT NOT NULL);";
	}
	else if (tableType == "INSTRUCTOR") {
		table = "CREATE TABLE INSTRUCTOR("
			"IID INTEGER PRIMARY KEY, "
			"NAME TEXT NOT NULL, "
			"SURNAME TEXT NOT NULL, "
			"TITLE TEXT NOT NULL, "
			"DEPT TEXT NOT NULL,"
			"DEGREE TEXT NOT NULL); ";
	}
	else if (tableType == "ADMIN") {
		table = "CREATE TABLE ADMIN("
			"AID INTEGER PRIMARY KEY, "
			"NAME TEXT NOT NULL, "
			"SURNAME TEXT NOT NULL, "
			"TITLE TEXT NOT NULL, "
			"OFFICE TEXT NOT NULL); ";
	}
	else if (tableType == "COURSE") {
		table = "CREATE TABLE COURSE("
			"CID INTEGER PRIMARY KEY, "
			"IID TEXT NOT NULL, "
			"TITLE TEXT NOT NULL, "
			"DEPARTMENT TEXT NOT NULL, "
			"TIME TEXT NOT NULL,"
			"DAYSOFWEEK TEXT NOT NULL, "
			"SEMESTER TEXT NOT NULL, "
			"YEAR TEXT NOT NULL, "
			"CREDITS INTEGER NOT NULL); ";
	}
	else {
		table = "CREATE TABLE ROSTER("
			"SID INTEGER NOT NULL, "
			"CID INTEGER NOT NULL); ";
	}

	try {
		int exit = 0;
		exit = sqlite3_open(s, &DB);

		char* messageError;
		exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK) {
			std::cerr << "Error Create " << tableType << " Table\n";
			sqlite3_free(messageError);
		}
		else {
			std::cout << tableType << " Table Created Successfully\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

	return 0;
}

// Function written by group
extern int clearTable(const char* s, std::string tableType) {
	
	sqlite3* DB;
	std::string sql;

	if (tableType == "STUDENT") {
		int exit = sqlite3_open(s, &DB);
		sql = "DELETE FROM STUDENT";
	}
	else if (tableType == "INSTRUCTOR") {
		int exit = sqlite3_open(s, &DB);
		sql = "DELETE FROM INSTRUCTOR";
	}
	else if (tableType == "ADMIN") {
		int exit = sqlite3_open(s, &DB);
		sql = "DELETE FROM ADMIN";
	}
	else if (tableType == "COURSE") {
		int exit = sqlite3_open(s, &DB);
		sql = "DELETE FROM COURSE";
	}
	else {
		int exit = sqlite3_open(s, &DB);
		sql = "DELETE FROM ROSTER";
	}

	sqlite3_exec(DB, sql.c_str(), callback_printData, NULL, NULL);

	return 0;
}

// Function written by group
extern int printTable(const char* s, std::string tableType) {
	
	sqlite3* DB;
	int exit = sqlite3_open(s, &DB);
	std::string query;

	if (tableType == "STUDENT") {
		query = "SELECT * FROM STUDENT;";
	}
	else if (tableType == "INSTRUCTOR") {
		query = "SELECT * FROM INSTRUCTOR;";
	}
	else if (tableType == "ADMIN") {
		query = "SELECT * FROM ADMIN;";
	}
	else if (tableType == "COURSE") {
		query = "SELECT * FROM COURSE;";
	}
	else {
		query = "SELECT ROSTER.CID, ROSTER.SID, STUDENT.NAME, STUDENT.SURNAME FROM ROSTER, STUDENT WHERE STUDENT.SID = ROSTER.SID ORDER BY ROSTER.CID;";
	}

	/* An open database, SQL to be evaluated, callbackPrint function, 1st argument to callbackPrint, Error msg written here */
	sqlite3_exec(DB, query.c_str(), callback_printData, NULL, NULL);

	return 0;
}

// Function written by Jackson Smith
extern int printCourse(const char* s, int courseID) { 
	
	sqlite3* DB;
	std::string query;
	int exit = sqlite3_open(s, &DB);

	query = "SELECT * FROM COURSE WHERE CID = ";
	query += std::to_string(courseID);
	query += ";";
	sqlite3_exec(DB, query.c_str(), callback_printData, NULL, NULL);

	return 0;
}

// Function written by Jackson Smith
extern int printStudentSchedule(const char* s, int userID) {
	
	sqlite3* DB;
	std::string query;
	std::vector<std::string> container;

	int exit = sqlite3_open(s, &DB);

	query = "SELECT * FROM ROSTER WHERE SID = ";
	query += std::to_string(userID);
	query += ";";
	sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

	if (container.size()) {
		for (int i = 0; i < container.size(); i++) {
			printCourse(s, std::stoi(container[i]));
		}
	}
	return 0;
}

extern int printCourseRoster(const char* s, int courseID) {
	
	sqlite3* DB;
	std::string query;
	std::vector<std::string> container;

	int exit = sqlite3_open(s, &DB);

	query = "SELECT SID FROM ROSTER WHERE CID = ";
	query += std::to_string(courseID);
	query += ";";
	sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

	if (container.size()) {
		//for (int i = 0; i < 2; i++) {
			printStudentData(s, std::stoi(container[0]));
		//}
	}
	return 0;
}

extern int printStudentData(const char* s, int studentID) {
	
	sqlite3* DB;
	int exit = sqlite3_open(s, &DB);
	std::string query;

	query = "SELECT SID, NAME, SURNAME FROM STUDENT;";

	/* An open database, SQL to be evaluated, callbackPrint function, 1st argument to callbackPrint, Error msg written here */
	sqlite3_exec(DB, query.c_str(), callback_printData, NULL, NULL);

	return 0;
}

// Function written by group
extern int loadInData(const char* s, int& numStudent, int& numInstructor, int& numAdmin) { 
	
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(s, &DB);

	std::string sql(
		"INSERT INTO STUDENT VALUES(1000, 'Jackson', 'Smith', 'BSCO', 2022, 4.00);"
		"INSERT INTO STUDENT VALUES(1001, 'Johnson', 'Goldsmith', 'BSEE', 1930, 4.00);"
		"INSERT INTO STUDENT VALUES(1002, 'Jayden', 'Locksmith', 'BSCE', 2010, 3.21);"
		"INSERT INTO STUDENT VALUES(1003, 'Jared', 'Smitty', 'BSCE', 2011, 3.25);"
		"INSERT INTO STUDENT VALUES(1004, 'Jaxson', 'Simmons', 'BSCS', 2018, 3.90);"
		"INSERT INTO STUDENT VALUES(1005, 'Kate', 'Smith', 'BSCO', 2023, 2.95);"
		"INSERT INTO STUDENT VALUES(1006, 'Mickey', 'Mouse', 'BSEE', 2024, 4.00);"
		"INSERT INTO STUDENT VALUES(1007, 'Goofy', 'Danger', 'BSCO', 2010, 3.25);"
		"INSERT INTO STUDENT VALUES(1008, 'Pluto', 'Yan', 'BSCE', 2015, 2.25);"
		"INSERT INTO STUDENT VALUES(1009, 'Bambi', 'Gate', 'BSCS', 2020, 3.70);"
		"INSERT INTO STUDENT VALUES(1010, 'Kirby', 'Smith', 'BSCO', 2021, 3.99);"

		"INSERT INTO INSTRUCTOR VALUES (2000, 'Ryan', 'Pasquel', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2001, 'Gary', 'Leung', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2002, 'Jane', 'Doe', 'Professor', 'PHY', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2003, 'Jack', 'Ripper', 'Professor', 'ENGL', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2004, 'Paul', 'Chan', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2005, 'Jerry', 'Lu', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2006, 'Trent', 'Forest', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2007, 'Will', 'Strange', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2008, 'Dustin', 'Potter', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2009, 'Mary', 'Black', 'Professor', 'ENG', 'PHD');"
		

		"INSERT INTO ADMIN VALUES(3000, 'Frank', 'Frankie', 'VP', 'Dobbs 202');"

		"INSERT INTO COURSE VALUES(4000, 2000, 'Applied Programming Concepts', 'ELEC', '8-9:50am', 'M T R', 'Summer', 2021, 4);"
		"INSERT INTO COURSE VALUES(4001, 2001, 'Signals and Systems', 'ELEC', '10-11:50am', 'T R', 'Summer', 2021, 3);"
		"INSERT INTO COURSE VALUES(4002, 2007, 'Computer Networks for Engineers', 'ELEC', '8-9:15am', 'W F', 'Summer', 2021, 4);"
		"INSERT INTO COURSE VALUES(4003, 2009, 'Advanced Digital Circuit Design', 'ELEC', '12:30-1:50pm', 'W F', 'Summer', 2021, 4);"
		"INSERT INTO COURSE VALUES(4004, 2008, 'Digital Logic', 'ELEC', '12:30-2:50', 'W T F', 'Fall', 2021, 4);"
		"INSERT INTO COURSE VALUES(4005, 2005, 'Hardware Security', 'ELEC', '1-2:50pm', 'T R', 'Summer', 2021, 3);"
		"INSERT INTO COURSE VALUES(4006, 2004, 'Object-Oriented Program', 'ELEC', '2-3:50', 'M w', 'Fall', 2021, 4);"
		"INSERT INTO COURSE VALUES(4007, 2006, 'Network Theory', 'ELEC', '8-8:50:', 'M T R', 'Spring', 2021, 4);"
		"INSERT INTO COURSE VALUES(4008, 2003, 'Engineering Physics', 'PHY', '12:30-1:50pm', 'W F', 'Spring', 2021, 4);"
		"INSERT INTO COURSE VALUES(4009, 2002, 'English', 'ENGL', '1-2:50pm', 'T R', 'Fall', 2021, 4);"

		"INSERT INTO ROSTER VALUES(1000, 4000);"
		"INSERT INTO ROSTER VALUES(1000, 4001);"
		"INSERT INTO ROSTER VALUES(1000, 4002);"
		"INSERT INTO ROSTER VALUES(1000, 4003);"
		"INSERT INTO ROSTER VALUES(1000, 4004);"

		"INSERT INTO ROSTER VALUES(1001, 4000);"
		"INSERT INTO ROSTER VALUES(1001, 4001);"
		"INSERT INTO ROSTER VALUES(1001, 4002);"
		"INSERT INTO ROSTER VALUES(1001, 4003);"
		"INSERT INTO ROSTER VALUES(1001, 4004);"

		"INSERT INTO ROSTER VALUES(1002, 4001);"
		"INSERT INTO ROSTER VALUES(1002, 4003);"

		"INSERT INTO ROSTER VALUES(1003, 4000);"
		"INSERT INTO ROSTER VALUES(1003, 4001);"
		"INSERT INTO ROSTER VALUES(1003, 4002);"
		"INSERT INTO ROSTER VALUES(1003, 4004);"
	);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Created Successfully!\n\n";
	}

	numStudent = 4;
	numInstructor = 2;
	numAdmin = 1;

	return 0;
}

// Functions written by group
extern int insertUser(const char* s, int userID, std::string firstName, std::string lastName, std::string major, int gradYear, float GPA) { // Student
	
	sqlite3* DB;
	char* messageError;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "INSERT INTO STUDENT VALUES(";
	sql += std::to_string(userID);
	sql += ", '";
	sql += firstName;
	sql += "', '";
	sql += lastName;
	sql += "', '";
	sql += major;
	sql += "', ";
	sql += std::to_string(gradYear);
	sql += ", ";
	sql += std::to_string(GPA);
	sql += ");";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Created Successfully!\n\n";
	}

	return 0;
}
extern int insertUser(const char* s, int userID, std::string firstName, std::string lastName, std::string title, std::string department, std::string degree) { // Instructor
	
	sqlite3* DB;
	char* messageError;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "INSERT INTO INSTRUCTOR VALUES(";
	sql += std::to_string(userID);
	sql += ", '";
	sql += firstName;
	sql += "', '";
	sql += lastName;
	sql += "', '";
	sql += title;
	sql += "', '";
	sql += department;
	sql += "', '";
	sql += degree;
	sql += "');";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Created Successfully!\n\n";
	}

	return 0;
}
extern int insertUser(const char* s, int userID, std::string firstName, std::string lastName, std::string title, std::string office) { // Admin
	
	sqlite3* DB;
	char* messageError;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "INSERT INTO ADMIN VALUES(";
	sql += std::to_string(userID);
	sql += ", '";
	sql += firstName;
	sql += "', '";
	sql += lastName;
	sql += "', '";
	sql += title;
	sql += "', '";
	sql += office;
	sql += "');";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Created Successfully!\n";
	}

	return 0;
}


extern int checkExistingUID(const char* s, int userID, bool& foundUID) {
	
	sqlite3* DB;
	std::string query;
	std::vector<std::string> container;

	int exit = sqlite3_open(s, &DB);

	foundUID = 0;
	int nextUserType = 1;
	switch (nextUserType) {
		case 1: {
			query = "SELECT SID FROM STUDENT WHERE SID = ";
			query += std::to_string(userID);
			query += ";";
			sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					foundUID = 1;
					break;
				}
			}
		}
		case 2: {
			query = "SELECT IID FROM INSTRUCTOR WHERE IID = ";
			query += std::to_string(userID);
			query += ";";
			sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					foundUID = 1;
					break;
				}
			}
		}
		case 3: {
			query = "SELECT AID FROM ADMIN WHERE AID = ";
			query += std::to_string(userID);
			query += ";";
			sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					foundUID = 1;
					break;
				}
			}
		}
	}
	return 0;
}
extern int checkExistingCID(const char* s, int courseID, bool& foundUID) {
	
	sqlite3* DB;
	std::string query;
	std::vector<std::string> container;

	int exit = sqlite3_open(s, &DB);

	foundUID = 0;
	query = "SELECT CID FROM COURSE WHERE CID = ";
	query += std::to_string(courseID);
	query += ";";
	sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

	if (container.size()) {
		if (container[0] == std::to_string(courseID)) {
			foundUID = 1;
		}
	}
	return 0;
}

// Function written by group
extern int signInUser(const char* s, int userID, int& userType, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* signedInAdmin) {
	
	sqlite3* DB;
	std::string query;
	std::vector<std::string> container;

	int exit = sqlite3_open(s, &DB);

	int nextUserType = 1;
	switch (nextUserType) {
		case 1: {
			query = "SELECT * FROM STUDENT WHERE SID = ";
			query += std::to_string(userID);
			query += ";";
			sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					signedInStudent->setAll(std::stoi(container[0]), container[1], container[2], container[3], std::stoi(container[4]), std::stof(container[5]));
					userType = 1;
					break;
				}
			}
		}
		case 2: {
			query = "SELECT * FROM INSTRUCTOR WHERE IID = ";
			query += std::to_string(userID);
			query += ";";
			sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					signedInInstructor->setAll(std::stoi(container[0]), container[1], container[2], container[3], container[4], container[5]);
					userType = 2;
					break;
				}
			}
		}
		case 3: {
			query = "SELECT * FROM ADMIN WHERE AID = ";
			query += std::to_string(userID);
			query += ";";
			sqlite3_exec(DB, query.c_str(), callback_getData, &container, NULL);

			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					signedInAdmin->setAll(std::stoi(container[0]), container[1], container[2], container[3], container[4]);
					userType = 3;
					break;
				}
			}
		}
	}
	return 0;
}

// Function written by Jackson Smith
extern int addStudent(const char* s, int userID, int courseID) {
	
	sqlite3* DB;
	char* messageError;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "INSERT INTO ROSTER VALUES(";
	sql += std::to_string(userID);
	sql += ", ";
	sql += std::to_string(courseID);
	sql += ");";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Created Successfully!\n\n";
	}

	return 0;
}
extern int dropStudent(const char* s, int userID, int courseID) {
	
	sqlite3* DB;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "DELETE FROM ROSTER WHERE SID = ";
	sql += std::to_string(userID);
	sql += " AND CID = ";
	sql += std::to_string(courseID);
	
	sqlite3_exec(DB, sql.c_str(), callback_printData, NULL, NULL);

	return 0;
}

extern int updateData(const char* s) {
	
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(s, &DB);

	std::string sql("UPDATE ADMIN SET TITLE = 'Vice President' WHERE ID = 3002");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Update\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Updated Successfully!\n";
	}

	return 0;
}
extern int insertCourse(const char* s, int courseID, int instructorID, std::string courseName, std::string department, std::string time, std::string daysOfWeek, std::string semester, int year, int credits) {

	sqlite3* DB;
	char* messageError;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "INSERT INTO COURSE VALUES(";
	sql += std::to_string(courseID);
	sql += ", ";
	sql += std::to_string(instructorID);
	sql += ", '";
	sql += courseName;
	sql += "', '";
	sql += department;
	sql += "', '";
	sql += time;
	sql += "', '";
	sql += daysOfWeek;
	sql += "', '";
	sql += semester;
	sql += "', ";
	sql += std::to_string(year);
	sql += ", ";
	sql += std::to_string(credits);
	sql += ");";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records Created Successfully!\n\n";
	}

	return 0;
}
extern int deleteCourse(const char* s, int courseID) {

	sqlite3* DB;
	std::string sql;

	int exit = sqlite3_open(s, &DB);

	sql = "DELETE FROM COURSE WHERE CID = ";
	sql += std::to_string(courseID);

	sqlite3_exec(DB, sql.c_str(), callback_printData, NULL, NULL);

	return 0;
}

// Function written by group
/* argc: holds the number of results, azColName: holds each column returned in array, argv: holds each value in array */
extern int callback_printData(void* NotUsed, int argc, char** argv, char** azColName) {
	
	for (int i = 0; i < argc; i++) {
		// column name and value
		std::cout << azColName[i] << ": " << argv[i] << "\n";
	}
	std::cout << "\n";

	return 0;
}

// Function written by group
extern int callback_getData(void* data, int argc, char** argv, char** azColName) {
	
	if (argc == 0)    //nothing in the row; shouldn’t happen
		return -1;

	auto& container = *static_cast<std::vector<std::string>*>(data);         //create vector

	if (!argv[0]) {                     //store data from the first column if it exists
		container.push_back("NULL");
	}
	else {
		for (int i = 0; i < argc; i++) {
			container.push_back(argv[i]);
		}
	}

	return 0;
}
