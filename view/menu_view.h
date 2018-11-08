#ifndef MANUFACTURY_MENU_VIEW_H
#define MANUFACTURY_MENU_VIEW_H

#include <global.h>
#include <curses.h>
#include <panel.h>
#include "hotkey.h"

void AllocateMenus(int count);

void CreateMenu(int id, wchar_t* label, int size, ...);

void InitMenu(void);


#endif //MANUFACTURY_MENU_VIEW_H
