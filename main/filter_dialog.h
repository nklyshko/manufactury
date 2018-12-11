#ifndef MANUFACTURY_FILTER_DIALOG_H
#define MANUFACTURY_FILTER_DIALOG_H

#include <curses.h>

void InitFilterDialog(int color);

void ShowFilterDialog(void (* onConfirm)(int fieldId, wchar_t* value));

#endif //MANUFACTURY_FILTER_DIALOG_H
