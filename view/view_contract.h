#ifndef MANUFACTURY_VIEW_CONTRACT_H
#define MANUFACTURY_VIEW_CONTRACT_H

#include <global.h>
#include <array.h>
#include "model_types.c"

void InitView(void);
void ShowTable(Array* data, int pos);
void StartControl(void);
void SetEntries(struct EmployeeList* employees);
void SetStatus(char* status);
void ShowProcessing(void);
void HideProcessing(void);
void ShowSaveDialog(); //Show WINAPI save dialog, save request to controller with selected filename
//void ShowError(chtype* error);
//void ShowEditor();
//void setTitle(string s);

#endif //MANUFACTURY_VIEW_CONTRACT_H
