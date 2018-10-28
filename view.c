#include <stdlib.h>
#include "global.h"

PANEL* title;
PANEL* table;
PANEL* status;
//PANEL* error;
//PANEL* loading;
//PANEL* menuView;
//PANEL* subMenuViews;

//File menu
void FileNew(void);
    //Redirect to controller
void FileOpen(void);
    //Show open dialog, request file open to controller with selected filename
void FileSave(void);
    //Redirect to controller(check if file already have name, or its new...)
void FileSaveAs(void);
    //Show save dialog, request file save to controller with selected filename


//Edit menu
void EditFind(void);

void EditAdd(void);

void EditDelete(void);

void EditChange(void);

//Tools menu
void ToolsExportCSV(void);

void ToolsCreateReport(void);

struct SubMenu {
    char* label;
    chtype hotkey;

    void (* action)(void);
};

struct Menu {
    char* label;
    int size;
    struct SubMenu** subMenu;
};

struct Menu* createMenu(char* label, int size, ...) {
    struct Menu* item = malloc(sizeof(struct Menu));
    item->label = label;
    item->size = size;
    item->subMenu = malloc(sizeof(struct subMenuItem*) * size);
    va_list args;
    va_start(args, (size * 3));
    for (int i = 0; i < size; i++) {
        struct SubMenu* subItem = malloc(sizeof(struct SubMenu));
        subItem->label = va_arg(args, char*);
        subItem->hotkey = va_arg(args, chtype);
        subItem->action = va_arg(args, void (*)(void));
        item->subMenu[i] = subItem;
    }
    va_end(args);
    return item;
}

const int menuSize = 3;
struct Menu** menu;

void initView(void) {
    menu = malloc(sizeof(struct Menu*) * menuSize);
    menu[0] = createMenu("Файл", 4,
                         "Новый", 'a', FileNew,
                         "Открыть", 'a', FileOpen,
                         "Сохранить", 'a', FileSave,
                         "Сохранить как...", 'a', FileSaveAs);
    menu[1] = createMenu("Правка", 4,
                         "Найти", 'a', EditFind,
                         "Добавить", 'a', EditAdd,
                         "Удалить", 'a', EditDelete,
                         "Изменить", 'a', EditChange);
    menu[2] = createMenu("Инструменты", 2,
                         "Экспорт в .CSV", 'a', ToolsExportCSV,
                         "Создать отчет", 'a', ToolsCreateReport);
}