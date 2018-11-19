#include <view/component.h>
#include <malloc.h>
#include <src/log.h>
#include "menu.h"

#define COLOR_MENU_LABEL 1
#define COLOR_MENU_LABEL_ACTIVE 2
#define COLOR_MENU_ITEM 3
#define COLOR_MENU_ITEM_ACTIVE 4

#define NOT_ACTIVE -1

void MenuSetPos(Menu* menu, int pos) {
    if (menu->pos == pos) return;
    WINDOW* w = menu->menuPanel->window;
    if (menu->pos != NOT_ACTIVE) {
        mvwchgat(w, menu->pos, 0, menu->width, 0, COLOR_MENU_ITEM, NULL);
    }
    menu->pos = pos;
    if (menu->pos != NOT_ACTIVE) {
        mvwchgat(w, menu->pos, 0, menu->width, 0, COLOR_MENU_ITEM_ACTIVE, NULL);
    }
}

void MenuLabelOnMouseClick(InteractivePanel* handle, MEVENT event) {
    Menu* menu = handle->holder->spec;
    if (menu->active) {
        PanelHide(menu->menuPanel);
        menu->active = false;
    } else {
        PanelShow(menu->menuPanel);
        menu->active = true;
    }
}

void MenuOnMouseClick(InteractivePanel* handle, MEVENT event) {
    Menu* menu = handle->holder->spec;
    int id = event.y;
    MenuItem* item = menu->items[id];
    item->action();
    FocusComponent(NULL);
}

void MenuShow(Component* handle) {
    Menu* menu = handle->spec;
    PanelShow(menu->labelPanel);
    if (menu->active) {
        PanelShow(menu->menuPanel);
    }
}

void MenuHide(Component* handle) {
    Menu* menu = handle->spec;
    PanelHide(menu->labelPanel);
    PanelHide(menu->menuPanel);
}

void MenuOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    Menu* menu = handle->spec;
    log_debug("MENU KEY: %d", key);
    if (key == KEY_DOWN) {
        if (menu->active) {
            if (menu->pos < menu->size - 1) MenuSetPos(menu, menu->pos + 1);
        }
    } else if (key == KEY_UP) {
        if (menu->active) {
            if (menu->pos > 0) MenuSetPos(menu, menu->pos - 1);
        }
    } else if (key == KEY_ENTER) {
        log_debug("MENU ENTER: %d", menu->pos);
        if (menu->pos != NOT_ACTIVE) {
            menu->items[menu->pos]->action();
            FocusComponent(NULL);
        }
    }
}

bool MenuOnFocusGet(Component* handle) {
    Menu* menu = handle->spec;
    wbkgd(menu->labelPanel->window, COLOR_PAIR(COLOR_MENU_LABEL_ACTIVE));
    MenuSetPos(menu, NOT_ACTIVE);
    return true;
}

bool MenuOnFocusChange(Component* handle) {
    Menu* menu = handle->spec;
    if (menu->active) {
        return false;
    } else {
        PanelShow(menu->menuPanel);
        MenuSetPos(menu, 0);
        menu->active = true;
        return true;
    }
}

void MenuOnFocusLost(Component* handle) {
    Menu* menu = handle->spec;
    wbkgd(menu->labelPanel->window, COLOR_PAIR(COLOR_MENU_LABEL));
    if (menu->active) {
        MenuSetPos(menu, NOT_ACTIVE);
        PanelHide(menu->menuPanel);
        menu->active = false;
    }
}

Component* CreateMenu(int x, int y, wchar_t* label, int size, ...) {
    Component* handle = CreateComponent();
    Menu* menu = malloc(sizeof(Menu));
    menu->pos = NOT_ACTIVE;
    menu->active = false;
    menu->label = label; //TODO: копировать строку
    menu->width = 0;
    menu->size = size;
    menu->items = malloc(sizeof(MenuItem*) * size);

    va_list args;
    va_start(args, (size * 3));
    for (int i = 0; i < size; i++) {
        MenuItem* item = malloc(sizeof(MenuItem));
        item->label = va_arg(args, wchar_t*);
        item->hotkey = va_arg(args, HotKey*);
        item->action = va_arg(args, void (*)(void));
        menu->items[i] = item;

        int len = (int) wcslen(item->label);
        if (len > menu->width) {
            menu->width = len;
        }

    }
    va_end(args);
    //ширина информации hotkey, пробел между заголовком и hotkey, отступы по бокам
    menu->width += 13 + 2 + 2;

    InteractivePanel* labelPanel = CreateInteractivePanel(handle, x, y, (int) wcslen(label) + 2, 1); //label width = len(label) + 2(spaces)
    wbkgd(labelPanel->window, COLOR_PAIR(COLOR_MENU_LABEL));
    mvwaddwstr(labelPanel->window, 0, 1, menu->label);
    labelPanel->OnMouseClick = MenuLabelOnMouseClick;
    menu->labelPanel = labelPanel;

    InteractivePanel* menuPanel = CreateInteractivePanel(handle, x, y + 1, menu->width, size);
    wbkgd(menuPanel->window, COLOR_PAIR(COLOR_MENU_ITEM));
    for (int i = 0; i < menu->size; i++) {
        MenuItem* item = menu->items[i];
        //пункт меню
        mvwaddwstr(menuPanel->window, i, 1, item->label);
        //hotkey
        wchar_t* h = GetHotKeyTitle(item->hotkey);
        mvwaddwstr(menuPanel->window, i, (int) (menu->width - 1 - wcslen(h)), h);
    }
    menuPanel->OnMouseClick = MenuOnMouseClick;
    menu->menuPanel = menuPanel;

    handle->spec = menu;
    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Menu", GetNextId());

    handle->Show = MenuShow;
    handle->Hide = MenuHide;
    handle->OnKeyClick = MenuOnKeyClick;
    handle->OnFocusGet = MenuOnFocusGet;
    handle->OnFocusChange = MenuOnFocusChange;
    handle->OnFocusLost = MenuOnFocusLost;
    return handle;
}