#include <model/data_source.h>
#include <model/array_ext.h>
#include <model/comparator.h>
#include <main/main_presenter.h>
#include "edit_presenter.h"
#include "edit_view.h"

Employee* currentEntry;

void addOnIdChange(int id) {
    if (id <= 0 || EmployeeIdExists(id)) {
        DataIdCorrectness(false);
    } else {
        DataIdCorrectness(true);
    }
}

void addOnConfirm(void) {
    Employee* e = GetEnteredData();
    AddEmployee(e);
    EntryAdded(e);
}

void addOnCancel(void) {

}


void ShowAddDialog(void) {
    Array* data = GetEmployees();
    int recommendedId = 1;
    if (array_size(data) > 0) {
        Employee* last;
        array_get_last(data, (void**) &last);
        recommendedId = last->id + 1;
    }
    ShowEmptyDialog(recommendedId, addOnIdChange, addOnConfirm, addOnCancel);
}

void editOnIdChange(int id) {
    if (id != currentEntry->id && (id <= 0 || EmployeeIdExists(id))) {
        DataIdCorrectness(false);
    } else {
        DataIdCorrectness(true);
    }
}

void editOnConfirm(void) {
    int id = GetEmployeeId();
    if (id != currentEntry->id) {
        currentEntry->id = id;
        ColumnChanged(FIELD_ID);
        KeyFieldChanged();
    }
    wchar_t* surname = GetEmployeeSurname();
    if (wcscmp(surname, currentEntry->surname) != 0) {
        EmployeeSetSurname(currentEntry, surname);
        ColumnChanged(FIELD_SURNAME);
    }
    wchar_t* name = GetEmployeeName();
    if (wcscmp(name, currentEntry->name) != 0) {
        EmployeeSetName(currentEntry, name);
        ColumnChanged(FIELD_NAME);
    }
    wchar_t* patronymic = GetEmployeePatronymic();
    if (wcscmp(patronymic, currentEntry->patronymic) != 0) {
        EmployeeSetPatronymic(currentEntry, patronymic);
        ColumnChanged(FIELD_PATRONYMIC);
    }
    int yob = GetEmployeeYOB();
    if (yob != currentEntry->yob) {
       currentEntry->yob = (short) yob;
        ColumnChanged(FIELD_YOB);
    }
    bool gender = GetEmployeeGender();
    if (gender != currentEntry->gender) {
        currentEntry->gender = gender;
        ColumnChanged(FIELD_GENDER);
    }
    wchar_t* profession = GetEmployeeProfession();
    if (wcscmp(profession, currentEntry->profession) != 0) {
        EmployeeSetProfession(currentEntry, profession);
        ColumnChanged(FIELD_PROFESSION);
    }
    int experience = GetEmployeeExperience();
    if (experience != currentEntry->experience) {
        currentEntry->experience = (char) experience;
        ColumnChanged(FIELD_EXPERIENCE);
    }
    ProfClass class = GetEmployeeClass();
    if (class != currentEntry->class) {
        currentEntry->class = class;
        ColumnChanged(FIELD_CLASS);
    }
    int department = GetEmployeeDepartment();
    if (department != currentEntry->department) {
        currentEntry->department = (char) department;
        ColumnChanged(FIELD_DEPARTMENT);
    }
    int plot = GetEmployeePlot();
    if (plot != currentEntry->plot) {
        currentEntry->plot = (char) plot;
        ColumnChanged(FIELD_PLOT);
    }
    int salary = GetEmployeeSalary();
    if (salary != currentEntry->salary) {
        currentEntry->salary = salary;
        ColumnChanged(FIELD_SALARY);
    }
    EntryChanged(currentEntry);
    currentEntry = NULL;
}

void editOnCancel(void) {
    currentEntry = NULL;
}

void ShowChangeDialog(Employee* e) {
    currentEntry = e;
    ShowDataDialog(e, editOnIdChange, editOnConfirm, editOnCancel);
}
