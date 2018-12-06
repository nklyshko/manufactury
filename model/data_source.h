#ifndef MANUFACTURY_DATA_SOURCE_H
#define MANUFACTURY_DATA_SOURCE_H

#include <array.h>
#include "data_types.h"

void InitDataSource(void);

void AddEmployee(Employee* e);

void RemoveEmployee(Employee* e);

bool EmployeeIdExists(int id);

Employee* GetEmployee(int id);

Array* GetEmployees(void);

bool ReadFile(char* fileName);

bool WriteFile(char* fileName);

bool BackupFile(char* fileName);

void WipeData(void);

void KeyFieldChanged(void);

#endif //MANUFACTURY_DATA_SOURCE_H
