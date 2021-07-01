#include "user.h"

/////////////////////////////////////////////////////
// * * * * * * * * * * STUDENT * * * * * * * * * * //
/////////////////////////////////////////////////////
void deleteAllStudents(std::list<student_c*> studentUsers) {

	std::list<student_c*>::iterator itBegin_S = studentUsers.begin();
	for (int i = 0; i < studentUsers.size(); i++, itBegin_S++) { delete* itBegin_S; }

	itBegin_S = studentUsers.begin();
	std::list<student_c*>::iterator itEnd_S = studentUsers.end();
	studentUsers.erase(itBegin_S, itEnd_S);
}

////////////////////////////////////////////////////////
// * * * * * * * * * * INSTRUCTOR * * * * * * * * * * //
////////////////////////////////////////////////////////
void deleteAllInstructors(std::list<instructor_c*> instructorUsers) {

	std::list<instructor_c*>::iterator itBegin_I = instructorUsers.begin();
	for (int i = 0; i < instructorUsers.size(); i++, itBegin_I++) { delete* itBegin_I; }

	itBegin_I = instructorUsers.begin();
	std::list<instructor_c*>::iterator itEnd_I = instructorUsers.end();
	instructorUsers.erase(itBegin_I, itEnd_I);
}

///////////////////////////////////////////////////
// * * * * * * * * * * ADMIN * * * * * * * * * * //
///////////////////////////////////////////////////
void deleteAllAdmin(std::list<admin_c*> adminUsers) {

	std::list<admin_c*>::iterator itBegin_A = adminUsers.begin();
	for (int i = 0; i < adminUsers.size(); i++, itBegin_A++) { delete* itBegin_A; }

	itBegin_A = adminUsers.begin();
	std::list<admin_c*>::iterator itEnd_A = adminUsers.end();
	adminUsers.erase(itBegin_A, itEnd_A);
}