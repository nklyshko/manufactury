#ifndef MANUFACTURY_DATA_TYPES_H
#define MANUFACTURY_DATA_TYPES_H

#include <curses.h>
#include <time.h>

#define SURNAME_LENGTH 16
#define NAME_LENGTH 16
#define PATRONYMIC_LENGTH 16
#define PROFESSION_LENGTH 16

typedef struct Employee Employee;
typedef enum ProfClass ProfClass;

enum ProfClass {
    FIRST = 1, SECOND = 2, THIRD = 3
};

struct Employee {
    int id;
    wchar_t surname[SURNAME_LENGTH];
    wchar_t name[NAME_LENGTH];
    wchar_t patronymic[PATRONYMIC_LENGTH];
    short yearOfBirth;
    bool gender;
    wchar_t profession[PROFESSION_LENGTH];
    char experience;
    ProfClass class;
    char departmentId;
    char plotId;
    int salary;
};

void EmployeeSetSurname(Employee* e, wchar_t* surname);

void EmployeeSetName(Employee* e, wchar_t* name);

void EmployeeSetPatronymic(Employee* e, wchar_t* patronymic);

void EmployeeSetProfession(Employee* e, wchar_t* profession);

bool ValueOfGender(int v);

ProfClass ValueOfProfClass(int v);

int parseInt(wchar_t* str);

#endif //MANUFACTURY_DATA_TYPES_H
