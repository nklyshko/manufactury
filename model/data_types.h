#ifndef MANUFACTURY_DATA_TYPES_H
#define MANUFACTURY_DATA_TYPES_H

#include <curses.h>

typedef struct Employee Employee;
typedef enum ProfClass ProfClass;

enum ProfClass {
    FIRST = 1, SECOND = 2, THIRD = 3
};

struct Employee {
    int id;
    wchar_t surname[16];
    wchar_t name[16];
    wchar_t patronymic[16];
    short yearOfBirth;
    bool gender;
    wchar_t profession[16];
    short experience;
    ProfClass class;
    int departmentId;
    int plotId;
    int salary;
    bool changed;
};

bool valueOfGender(wchar_t* str);

ProfClass valueOfProfClass(wchar_t* str);

#endif //MANUFACTURY_DATA_TYPES_H
