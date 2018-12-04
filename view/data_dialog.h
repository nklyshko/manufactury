#ifndef MANUFACTURY_DATA_DIALOG_H
#define MANUFACTURY_DATA_DIALOG_H

#include <model/data_types.h>
#include "layout.h"

void InitDataDialog(int color);

void ShowAddDialog(void (* onConfirm)(void), void (* onCancel)(void));

void ShowEditDialog(Employee* e, void (* onConfirm)(void), void (* onCancel)(void));

Employee* GetEnteredData();

#endif //MANUFACTURY_DATA_DIALOG_H
