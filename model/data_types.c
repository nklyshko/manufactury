#include <src/log.h>
#include "data_types.h"

void EmployeeSetSurname(Employee* e, wchar_t* surname) {
    wmemcpy_s(e->surname, SURNAME_LENGTH + 1, surname, SURNAME_LENGTH + 1);
}

void EmployeeSetName(Employee* e, wchar_t* name) {
    wmemcpy_s(e->name, NAME_LENGTH + 1, name, NAME_LENGTH + 1);
}

void EmployeeSetPatronymic(Employee* e, wchar_t* patronymic) {
    wmemcpy_s(e->patronymic, PATRONYMIC_LENGTH + 1, patronymic, PATRONYMIC_LENGTH + 1);
}

void EmployeeSetProfession(Employee* e, wchar_t* profession) {
    wmemcpy_s(e->profession, PROFESSION_LENGTH + 1, profession, PROFESSION_LENGTH + 1);
}

bool ValueOfGender(int v) {
    return v == 0;
}

ProfClass ValueOfProfClass(int v) {
    if (v < 0 || v > 2) return FIRST;
    return v + 1;
}

int parseInt(wchar_t* str) {
    int num = 0;
    int i = 0;
    while(str[i] != L'\0') {
        if (str[i] < 48 || str[i] > 57) return 0;
        num = num * 10 + (str[i] - 48);
        i++;
    }
    return num;
}
