#ifndef MANUFACTURY_EDIT_VIEW_H
#define MANUFACTURY_EDIT_VIEW_H

#include <model/data_types.h>
#include <tui/component.h>

void InitDataDialog(int color);

void ShowEmptyDialog(int recommendedId, void (*onIdChange)(int id), void (* onConfirm)(void), void (* onCancel)(void));

void ShowDataDialog(Employee* e, void (*onIdChange)(int id), void (* onConfirm)(void), void (* onCancel)(void));

int GetEmployeeId(void);

wchar_t* GetEmployeeSurname(void);

wchar_t* GetEmployeeName(void);

wchar_t* GetEmployeePatronymic(void);

int GetEmployeeYOB(void);

bool GetEmployeeGender(void);

wchar_t* GetEmployeeProfession(void);

int GetEmployeeExperience(void);

ProfClass GetEmployeeClass(void);

int GetEmployeeDepartment(void);

int GetEmployeePlot(void);

int GetEmployeeSalary(void);

Employee* GetEnteredData(void);

void DataIdCorrectness(bool correct);

#endif //MANUFACTURY_EDIT_VIEW_H
