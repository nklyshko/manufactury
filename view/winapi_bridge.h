#ifndef MANUFACTURY_MESSAGE_BOX_H
#define MANUFACTURY_MESSAGE_BOX_H

#include <curses.h>

void ShowMessage(wchar_t* message);

bool ShowOpenFileDialog(char* fileName, int maxLength);

bool ShowSaveFileDialog(char* fileName, int maxLength);

#endif //MANUFACTURY_MESSAGE_BOX_H
