#ifndef MANUFACTURY_MAIN_PRESENTER_H
#define MANUFACTURY_MAIN_PRESENTER_H

#include <model/data_types.h>
#include <model/comparator.h>
#include <tui/layout.h>
#include <tui/interactive_panel.h>
#include "global.h"

void InitApplication(char* param);

void FileNew(void);

void FileOpen(void);

void FileSave(void);

void FileSaveAs(void);

void EditAdd(void);

void EditDelete(void);

void EditChange(void);

void ToolsExportCSV(void);

void ToolsCreateReport(void);

void TableOnScrollDown(ScrollType scrollType);

void TableOnScrollUp(ScrollType scrollType);

void SortData(int fieldId, SortDirection direction);

void EditEntry(Component* handle);

void OnIdButtonMouseClick(InteractivePanel* handle, MEVENT event);

void OnIdButtonKeyClick(Component* handle, int key, unsigned long modifiers);

void ColumnChanged(int fieldId);

void ChangeSurname(Component* handle);

void ChangeName(Component* handle);

void ChangePatronymic(Component* handle);

void ChangeYOB(Component* handle);

void ChangeGender(Component* handle);

void ChangeProfession(Component* handle);

void ChangeExperience(Component* handle);

void ChangeClass(Component* handle);

void ChangeDepartment(Component* handle);

void ChangePlot(Component* handle);

void ChangeSalary(Component* handle);

void EntryAdded(Employee* e);

void EntryChanged(Employee* e);

////Edit menu
//void EditFind(void);

#endif //MANUFACTURY_MAIN_PRESENTER_H
