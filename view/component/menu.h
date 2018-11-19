#ifndef MANUFACTURY_MENU_H
#define MANUFACTURY_MENU_H

#include <view/hotkey.h>
#include <view/interactive_panel.h>

typedef struct Menu Menu;
typedef struct MenuItem MenuItem;
typedef struct MenuStyle MenuStyle;

struct Menu {
    MenuStyle* style;
    wchar_t* label;
    int pos;
    bool active;
    int width;
    int size;
    InteractivePanel* labelPanel;
    InteractivePanel* menuPanel;
    MenuItem** items;
};

struct MenuItem {
    wchar_t* label;
    HotKey* hotkey;
    void (* action)(void);
};

struct MenuStyle {
    int defaultLabel;
    int activeLabel;
    int defaultItem;
    int activeItem;
};

Component* CreateMenu(MenuStyle* style, int x, int y, wchar_t* label, int size, ...);

MenuStyle* CreateMenuStyle(int defaultLabel, int activeLabel, int defaultItem, int activeItem);

#endif //MANUFACTURY_MENU_H
