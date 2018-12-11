#include "predicate.h"

int EmployeeIdPredicate(int* value, Employee* e) {
    return *value - e->id;
}

int EmployeeSurnamePredicate(wchar_t* value, Employee* e) {
    return wcscmp(value, e->surname);
}

int EmployeeNamePredicate(wchar_t* value, Employee* e) {
    return wcscmp(value, e->name);
}

int EmployeePatronymicPredicate(wchar_t* value, Employee* e) {
    return wcscmp(value, e->patronymic);
}

int EmployeeYOBPredicate(int* value, Employee* e) {
    return *value - e->yob;
}

int EmployeeGenderPredicate(bool* value, Employee* e) {
    return *value - e->gender;
}

int EmployeeProfessionPredicate(wchar_t* value, Employee* e) {
    return wcscmp(value, e->profession);
}

int EmployeeExperiencePredicate(int* value, Employee* e) {
    return *value - e->experience;
}

int EmployeeClassPredicate(ProfClass* value, Employee* e) {
    return *value - e->class;
}

int EmployeeDepartmentPredicate(int* value, Employee* e) {
    return *value - e->department;
}

int EmployeePlotPredicate(int* value, Employee* e) {
    return *value - e->plot;
}

int EmployeeSalaryPredicate(int* value, Employee* e) {
    return *value - e->salary;
}