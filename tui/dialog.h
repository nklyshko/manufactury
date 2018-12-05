#ifndef MANUFACTURY_DIALOG_H
#define MANUFACTURY_DIALOG_H

#include "layout.h"

void InitDialogsLayouts(int color);

void ShowConfirmationDialog(wchar_t* message, void (* onYes)(void), void (* onNo)(void), void (* onCancel)(void));

void ShowMessageDialog(wchar_t* message, void (* onOk)(void));

#endif //MANUFACTURY_DIALOG_H
