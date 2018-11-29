#ifndef MANUFACTURY_COMPARATORS_H
#define MANUFACTURY_COMPARATORS_H

#include <malloc.h>
#include "data_types.h"

typedef struct Comparator Comparator;
typedef enum SortDirection SortDirection;

enum SortDirection { NONE, ASC, DSC};

struct Comparator {
    int (* compare)(Employee** e1, Employee** e2);
    int (* compareReversed)(Employee** e1, Employee** e2);
};

Comparator* CreateComparator(
        int (* compare)(Employee** e1, Employee** e2),
        int (* compareReversed)(Employee** e1, Employee** e2));

int EmployeeIdComparator(Employee** e1, Employee** e2);

int EmployeeSurnameComparator(Employee** e1, Employee** e2);

int EmployeeNameComparator(Employee** e1, Employee** e2);

int EmployeePatronymicComparator(Employee** e1, Employee** e2);

int EmployeeYOBComparator(Employee** e1, Employee** e2);

int EmployeeGenderComparator(Employee** e1, Employee** e2);

int EmployeeProfessionComparator(Employee** e1, Employee** e2);

int EmployeeExperienceComparator(Employee** e1, Employee** e2);

int EmployeeClassComparator(Employee** e1, Employee** e2);

int EmployeeDepartmentComparator(Employee** e1, Employee** e2);

int EmployeePlotComparator(Employee** e1, Employee** e2);

int EmployeeSalaryComparator(Employee** e1, Employee** e2);

int EmployeeIdComparatorReversed(Employee** e1, Employee** e2);

int EmployeeSurnameComparatorReversed(Employee** e1, Employee** e2);

int EmployeeNameComparatorReversed(Employee** e1, Employee** e2);

int EmployeePatronymicComparatorReversed(Employee** e1, Employee** e2);

int EmployeeYOBComparatorReversed(Employee** e1, Employee** e2);

int EmployeeGenderComparatorReversed(Employee** e1, Employee** e2);

int EmployeeProfessionComparatorReversed(Employee** e1, Employee** e2);

int EmployeeExperienceComparatorReversed(Employee** e1, Employee** e2);

int EmployeeClassComparatorReversed(Employee** e1, Employee** e2);

int EmployeeDepartmentComparatorReversed(Employee** e1, Employee** e2);

int EmployeePlotComparatorReversed(Employee** e1, Employee** e2);

int EmployeeSalaryComparatorReversed(Employee** e1, Employee** e2);

#endif //MANUFACTURY_COMPARATORS_H
