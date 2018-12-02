#ifndef MANUFACTURY_DIALOG_H
#define MANUFACTURY_DIALOG_H

#include "layout.h"

void InitDialogLayout(int color);

void ShowDialog(wchar_t* message, void (* onYes)(void), void (* onNo)(void), void (* onCancel)(void));

#endif //MANUFACTURY_DIALOG_H
