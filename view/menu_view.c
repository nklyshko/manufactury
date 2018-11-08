#include <src/log.h>
#include "menu_view.h"
#include "mouse_handler.h"
#include "styles.h"

#define NOT_ACTIVE -1

typedef struct {
    wchar_t* label;
    HotKey hotkey;
    void (* action)(void);
} MenuItem;

typedef struct {
    wchar_t* label;
    int pos;
    int width;
    int size;
    PANEL* panel;
    MenuItem** items;
} Menu;


void DrawMenuLabel(Menu* menu, bool active);
void ActiveMenu(Menu* menu);


WINDOW* window;
PANEL* panel;

int menusCount = 0;
Menu** menus;

Menu* activeMenu = NULL;
int activeMenuItem = NOT_ACTIVE;


void MenusBarMouseHandler(PANEL* _, MEVENT event) {
    Menu* m = NULL;
    if (event.bstate & BUTTON1_CLICKED || event.bstate & BUTTON1_PRESSED) {
        if (event.y == 0) {
            for (int i = 0; i < menusCount; i++) {
                if (event.x >= menus[i]->pos && event.x < (menus[i]->pos + menus[i]->width)) {
                    m = menus[i];
                    break;
                }
            }
            ActiveMenu(m);
        }
    }
}

void MenuMouseHandler(PANEL* panel, MEVENT event) {
    MouseHandler* handler = (MouseHandler*) panel_userptr(panel);
    Menu* menu = (Menu*) handler->attribute;
    if (event.bstate & BUTTON1_CLICKED) {
        MenuItem* item = menu->items[event.y];
        if (item != NULL) {
            if (item->action != NULL) {
                ActiveMenu(NULL);
                (item->action)();
            }
        }
    }
}

void ActiveMenu(Menu* menu) {
    if (activeMenu != NULL) {
        DrawMenuLabel(activeMenu, FALSE);
        hide_panel(activeMenu->panel);
    }
    if (menu != NULL) {
        activeMenu = menu;
        DrawMenuLabel(menu, TRUE);
        show_panel(menu->panel);
    } else {
        activeMenu = NULL;
    }
}

void DrawMenuLabel(Menu* menu, bool active) {
    wmove(window, 0, menu->pos);
    wattrset(window, active ? COLOR_PAIR(COLOR_MENU_ACTIVE) : COLOR_PAIR(COLOR_MENU));
    waddch(window, ' ');
    waddwstr(window, menu->label);
    waddch(window, ' ');
}

void AllocateMenus(int count) {
    free(menus);
    menus = NULL;
    menusCount = 0;

    menus = malloc(sizeof(Menu*) * count);
    if (menus != NULL) {
        menusCount = count;
    }
}

void CreateMenu(int id, wchar_t* label, int size, ...) {
    if (id >= menusCount) return;

    Menu* menu = malloc(sizeof(Menu));
    menu->label = label;
    menu->width = (int) wcslen(label);
    menu->size = size;
    menu->items = malloc(sizeof(MenuItem*) * size);

    va_list args;
    va_start(args, (size * 3));
    for (int i = 0; i < size; i++) {
        MenuItem* item = malloc(sizeof(MenuItem));
        item->label = va_arg(args, wchar_t*);
        item->hotkey = va_arg(args, HotKey);
        item->action = va_arg(args, void (*)(void));

        menu->items[i] = item;
    }
    va_end(args);
    menus[id] = menu;
}

void InitMenu() {
    window = newwin(1, TERMINAL_WIDTH, 1, 0);
    panel = new_panel(window);
    MouseHandler* mouseHandler = malloc(sizeof(MouseHandler));
    mouseHandler->clickInEvent = MenusBarMouseHandler;
    mouseHandler->attribute = NULL;
    set_panel_userptr(panel, mouseHandler);
    int pos = 0;
    for (int i = 0; i < menusCount; i++) {
        Menu* menu = menus[i];
        menu->pos = pos;
        menu->width = (int) (wcslen(menu->label) + 2);
        pos += menu->width;
        wattrset(window, COLOR_PAIR(COLOR_MENU));
        waddch(window, ' ');
        waddwstr(window, menu->label);
        waddch(window, ' ');

        //ширина панели с пунктами меню
        int menuWidth = 0;

        for (int j = 0; j < menu->size; j++) {
            int len = (int) wcslen(menu->items[j]->label);
            if (len > menuWidth) {
                menuWidth = len;
            }
        }

        //ширина информации hotkey, пробел между заголовком и hotkey, отступы по бокам
        menuWidth += 13 + 2 + 2;

        WINDOW* w = newwin(menu->size, menuWidth, 2, menu->pos);

        wbkgd(w, COLOR_PAIR(COLOR_MENU_ITEM));
        for (int j = 0; j < menu->size; j++) {
            MenuItem* item = menu->items[j];
            //пункт меню
            mvwaddwstr(w, j, 1, item->label);
            //hotkey
            wchar_t* h = GetHotKeyTitle(item->hotkey);
            mvwaddwstr(w, j, (int) (menuWidth - 1 - wcslen(h)), h);
        }
        menu->panel = new_panel(w);

        MouseHandler* handler = malloc(sizeof(MouseHandler));
        handler->clickInEvent = MenuMouseHandler;
        handler->attribute = menu;

        set_panel_userptr(menu->panel, handler);

        hide_panel(menu->panel);
    }
}