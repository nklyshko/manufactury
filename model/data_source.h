#ifndef MANUFACTURY_DATA_SOURCE_H
#define MANUFACTURY_DATA_SOURCE_H

#include <array.h>
#include "data_types.h"

void InitDataSource(void);

void AddEmployee(Employee* e);

void RemoveEmployee(Employee* e);

bool EmployeeIdExists(Employee* e);

Array* GetEmployees(void);

bool ReadFile(char* fileName);

bool WriteFile(char* fileName);

bool BackupFile(char* fileName);

void WipeData(void);

#endif //MANUFACTURY_DATA_SOURCE_H
