#include "user.h"

extern int createDB(const char* s) {
	
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

extern int createTable(const char* s, std::string tableType) {
	
	sqlite3* DB;

	std::string table;
	if (tableType == "STUDENT") {
		table = "CREATE TABLE STUDENT("
			"UID INTEGER PRIMARY KEY, "
			"NAME TEXT NOT NULL, "
			"SURNAME TEXT NOT NULL, "
			"MAJOR TEXT NOT NULL, "
			"GRADYEAR INTEGER NOT NULL,"
			"GPA FLOAT NOT NULL);";
	}
	else if (tableType == "INSTRUCTOR") {
		table = "CREATE TABLE INSTRUCTOR("
			"UID INTEGER PRIMARY KEY, "
			"NAME TEXT NOT NULL, "
			"SURNAME TEXT NOT NULL, "
			"TITLE TEXT NOT NULL, "
			"DEPT TEXT NOT NULL,"
			"DEGREE TEXT NOT NULL); ";
	}
	else if (tableType == "ADMIN") {
		table = "CREATE TABLE ADMIN("
			"UID INTEGER PRIMARY KEY, "
			"NAME TEXT NOT NULL, "
			"SURNAME TEXT NOT NULL, "
			"TITLE TEXT NOT NULL, "
			"OFFICE TEXT NOT NULL); ";
	}
	else {
		table = "CREATE TABLE COURSE("
			"CID INTEGER PRIMARY KEY, "
			"TITLE TEXT NOT NULL, "
			"DEPARTMENT TEXT NOT NULL, "
			"TIME TEXT NOT NULL,"
			"DAYSOFWEEK TEXT NOT NULL, "
			"SEMESTER TEXT NOT NULL, "
			"YEAR TEXT NOT NULL, "
			"CREDITS INTEGER NOT NULL); ";
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
	else {
		int exit = sqlite3_open(s, &DB);
		sql = "DELETE FROM COURSE";
	}
	sqlite3_exec(DB, sql.c_str(), callback_print, NULL, NULL);

	return 0;
}

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
	else {
		query = "SELECT * FROM COURSE;";
	}

	/* An open database, SQL to be evaluated, callbackPrint function, 1st argument to callbackPrint, Error msg written here */
	sqlite3_exec(DB, query.c_str(), callback_print, NULL, NULL);

	return 0;
}

extern int loadInData(const char* s, int& numStudent, int& numInstructor, int& numAdmin) {
	
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(s, &DB);

	std::string sql("INSERT INTO STUDENT VALUES(1000, 'Jackson', 'Smith', 'BSCO', 2022, 4.00);"
		"INSERT INTO STUDENT VALUES(1001, 'Johnson', 'Goldsmith', 'BSEE', 1928, 4.00);"
		"INSERT INTO STUDENT VALUES(1002, 'Jayden', 'Locksmith', 'BSCE', 2010, 3.21);"
		"INSERT INTO STUDENT VALUES(1003, 'Jared', 'Smitty', 'BSCE', 2011, 3.25);"
		"INSERT INTO INSTRUCTOR VALUES (2000, 'Ryan', 'Pasquel', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO INSTRUCTOR VALUES (2001, 'Gary', 'Leung', 'Professor', 'ENG', 'PHD');"
		"INSERT INTO ADMIN VALUES(3000, 'Frank', 'Frankie', 'VP', 'Dobbs 202');"
		"INSERT INTO COURSE VALUES(4000, 'Applied Programming Concepts', 'ELEC', '8-9:50am', 'M T R', 'Summer', 2021, 4);"
		"INSERT INTO COURSE VALUES(4000, 'Signals and Systems', 'ELEC', '10-11:50am', 'T R', 'Summer', 2021, 4);"
		"INSERT INTO COURSE VALUES(4000, 'Computer Networks for Engineers', 'ELEC', '8-9:15am', 'W F', 'Summer', 2021, 4);"
		"INSERT INTO COURSE VALUES(4001, 'Advanced Digital Circuit Design', 'ELEC', '12:30-1:50pm', 'W F', 'Summer', 2021, 4);"
	);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Inserttttttttttttttt\n";
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

extern int insertUser(const char* s, int userID, std::string firstName, std::string lastName, std::string major, int gradYear, float GPA) { // Student
	
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "INSERT INTO STUDENT VALUES(";
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

	int exit = sqlite3_open(s, &DB);

	std::string sql = "INSERT INTO INSTRUCTOR VALUES(";
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

	int exit = sqlite3_open(s, &DB);

	std::string sql = "INSERT INTO ADMIN VALUES(";
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

extern int signInUser(const char* s, int userID, int& userType, student_c* signedInStudent, instructor_c* signedInInstructor, admin_c* signedInAdmin) {
	
	sqlite3* DB;
	std::string query;
	std::vector<std::string> container;

	int exit = sqlite3_open(s, &DB);

	int nextUserType = 1;
	switch (nextUserType) {
		case 1: {
			query = "SELECT * FROM STUDENT WHERE UID = ";
			query += std::to_string(userID);
			query += ";";
			std::cout << "Before student sqlite_exec()\n";
			exit = sqlite3_exec(DB, query.c_str(), callback_newUser, &container, NULL);
			std::cout << "After student sqlite_exec()\n";
			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					signedInStudent->setAll(std::stoi(container[0]), container[1], container[2], container[3], std::stoi(container[4]), std::stof(container[5]));
					userType = 1;
					break;
				}
			}
		}
		case 2: {
			query = "SELECT * FROM INSTRUCTOR WHERE UID = ";
			query += std::to_string(userID);
			query += ";";
			std::cout << "Before instructor sqlite_exec()\n";
			exit = sqlite3_exec(DB, query.c_str(), callback_newUser, &container, NULL);
			std::cout << "After instructor sqlite_exec()\n";
			if (container.size()) {
				if (container[0] == std::to_string(userID)) {
					signedInInstructor->setAll(std::stoi(container[0]), container[1], container[2], container[3], container[4], container[5]);
					userType = 2;
					break;
				}
			}
		}
		case 3: {
			query = "SELECT * FROM ADMIN WHERE UID = ";
			query += std::to_string(userID);
			query += ";";
			std::cout << "Before admin sqlite_exec()\n";
			exit = sqlite3_exec(DB, query.c_str(), callback_newUser, &container, NULL);
			std::cout << "After admin sqlite_exec()\n";
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

/* argc: holds the number of results, azColName: holds each column returned in array, argv: holds each value in array */
extern int callback_print(void* NotUsed, int argc, char** argv, char** azColName) {
	
	for (int i = 0; i < argc; i++) {
		// column name and value
		std::cout << azColName[i] << ": " << argv[i] << "\n";
	}
	std::cout << "\n";

	return 0;
}

extern int callback_newUser(void* data, int argc, char** argv, char** azColName) {
	
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