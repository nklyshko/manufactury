#ifndef MANUFACTURY_MODEL_TYPES
#define MANUFACTURY_MODEL_TYPES

#include "global.h"

struct EmployeeListEntry {
    struct EmployeeListEntry* next;
    struct EmployeeListEntry* prev;
    struct EmployeeData* data;
};

struct EmployeeList {
    struct EmployeeListEntry* first;
    struct EmployeeListEntry* last;
    int size;
};

struct Employee {
    int id;
    chtype name[16];
    chtype surname[16];
    chtype patronymic[16];
    short yearOfBirth;
    bool gender;
    chtype profession[16];
    short experience;
    unsigned char class;
    int departmentId;
    int plotId;
    int salary;
};

#endif //MANUFACTURY_TYPES