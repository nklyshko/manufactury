#include <src/log.h>
#include "comparator.h"

Comparator* CreateComparator(int (* compare)(Employee**, Employee**), int (* compareReversed)(Employee**, Employee**)) {
    Comparator* c = malloc(sizeof(Comparator));
    c->compare = compare;
    c->compareReversed = compareReversed;
    return c;
}

int EmployeeIdComparator(Employee** e1, Employee** e2) {
    return (*e1)->id - (*e2)->id;
}

int EmployeeSurnameComparator(Employee** e1, Employee** e2) {
    return wcscmp((*e1)->surname, (*e2)->surname);
}

int EmployeeNameComparator(Employee** e1, Employee** e2) {
    return wcscmp((*e1)->name, (*e2)->name);
}

int EmployeePatronymicComparator(Employee** e1, Employee** e2) {
    return wcscmp((*e1)->patronymic, (*e2)->patronymic);
}

int EmployeeYOBComparator(Employee** e1, Employee** e2) {
    return (*e1)->yearOfBirth - (*e2)->yearOfBirth;
}

int EmployeeGenderComparator(Employee** e1, Employee** e2) {
    return (*e1)->gender - (*e2)->gender;
}

int EmployeeProfessionComparator(Employee** e1, Employee** e2) {
    return wcscmp((*e1)->profession, (*e2)->profession);
}

int EmployeeExperienceComparator(Employee** e1, Employee** e2) {
    return (*e1)->experience - (*e2)->experience;
}

int EmployeeClassComparator(Employee** e1, Employee** e2) {
    return (*e1)->class - (*e2)->class;
}

int EmployeeDepartmentComparator(Employee** e1, Employee** e2) {
    return (*e1)->departmentId - (*e2)->departmentId;
}

int EmployeePlotComparator(Employee** e1, Employee** e2) {
    return (*e1)->plotId - (*e2)->plotId;
}

int EmployeeSalaryComparator(Employee** e1, Employee** e2) {
    return (*e1)->salary - (*e2)->salary;
}

int EmployeeIdComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeIdComparator(e1, e2);
}

int EmployeeSurnameComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeSurnameComparator(e1, e2);
}

int EmployeeNameComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeNameComparator(e1, e2);
}

int EmployeePatronymicComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeePatronymicComparator(e1, e2);
}

int EmployeeYOBComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeYOBComparator(e1, e2);
}

int EmployeeGenderComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeGenderComparator(e1, e2);
}

int EmployeeProfessionComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeProfessionComparator(e1, e2);
}

int EmployeeExperienceComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeExperienceComparator(e1, e2);
}

int EmployeeClassComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeClassComparator(e1, e2);
}

int EmployeeDepartmentComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeDepartmentComparator(e1, e2);
}

int EmployeePlotComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeePlotComparator(e1, e2);
}

int EmployeeSalaryComparatorReversed(Employee** e1, Employee** e2) {
    return -1 * EmployeeSalaryComparator(e1, e2);
}
