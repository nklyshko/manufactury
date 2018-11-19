#ifndef MANUFACTURY_MENU_H
#define MANUFACTURY_MENU_H

#include <view/hotkey.h>
#include <view/interactive_panel.h>

typedef struct MenuItem MenuItem;

struct MenuItem {
    wchar_t* label;
    HotKey* hotkey;
    void (* action)(void);
};

typedef struct Menu Menu;

struct Menu {
    wchar_t* label;
    int pos;
    bool active;
    int width;
    int size;
    InteractivePanel* labelPanel;
    InteractivePanel* menuPanel;
    MenuItem** items;
};

Component* CreateMenu(int x, int y, wchar_t* label, int size, ...);

#endif //MANUFACTURY_MENU_H
