#ifndef MANUFACTURY_PREDICATE_H
#define MANUFACTURY_PREDICATE_H

#include "data_types.h"

int EmployeeIdPredicate(int* value, Employee* e);

int EmployeeSurnamePredicate(wchar_t* value, Employee* e);

int EmployeeNamePredicate(wchar_t* value, Employee* e);

int EmployeePatronymicPredicate(wchar_t* value, Employee* e);

int EmployeeYOBPredicate(int* value, Employee* e);

int EmployeeGenderPredicate(bool* value, Employee* e);

int EmployeeProfessionPredicate(wchar_t* value, Employee* e);

int EmployeeExperiencePredicate(int* value, Employee* e);

int EmployeeClassPredicate(ProfClass* value, Employee* e);

int EmployeeDepartmentPredicate(int* value, Employee* e);

int EmployeePlotPredicate(int* value, Employee* e);

int EmployeeSalaryPredicate(int* value, Employee* e);

#endif //MANUFACTURY_PREDICATE_H
