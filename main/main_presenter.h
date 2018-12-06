#ifndef MANUFACTURY_MAIN_PRESENTER_H
#define MANUFACTURY_MAIN_PRESENTER_H

#include <model/data_types.h>
#include <model/comparator.h>
#include <tui/layout.h>
#include "global.h"

void InitApplication(char* param);

void FileNew(void);

void FileOpen(void);

void FileSave(void);

void FileSaveAs(void);

void EditAdd(void);;

void ToolsExportCSV(void);

void TableOnScrollDown(ScrollType scrollType);

void TableOnScrollUp(ScrollType scrollType);

void SortData(int fieldId, SortDirection direction);

void ColumnUpdated(int fieldId);

void ChangeSurname(Component* handle);

void EntryAdded(Employee* e);

////Redirect to controller(check if file already have name, or its new...)
//void FileSaveAs(void);
////Show save dialog, request file save to controller with selected filename
//
////Edit menu
//void EditFind(void);
//
//void EditAdd(void);
//
//void EditDelete(void);
//
//void EditChange(void);
//
////Tools menu
//
//void ToolsCreateReport(void);

#endif //MANUFACTURY_MAIN_PRESENTER_H
