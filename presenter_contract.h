#ifndef MANUFACTURY_CONTROLLER_CONTRACT_H
#define MANUFACTURY_CONTROLLER_CONTRACT_H

#include <view/layout.h>
#include <model/data_types.h>
#include <model/comparator.h>
#include "global.h"

void InitApplication(char* param);

void FileOpen(void);

void TableOnScrollDown(ScrollType scrollType);

void TableOnScrollUp(ScrollType scrollType);

void SortData(Comparator* comparator, SortDirection direction);

////Show open dialog, request file open to controller with selected filename
//void FileSave(void);
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
//void ToolsExportCSV(void);
//
//void ToolsCreateReport(void);

#endif //MANUFACTURY_CONTROLLER_CONTRACT_H
