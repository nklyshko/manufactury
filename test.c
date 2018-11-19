#include <curses.h>
#include <panel.h>
#include <view/component.h>
#include <view/component/edit.h>
#include <view/component/label.h>
#include <view/layout.h>
#include <view/component/menu.h>
#include <view/styles.h>
#include <view/component/button.h>
#include "src/log.h"
#include "view/hotkey.h"

//#ifndef MANUFACTURY_VERSION
//#define MANUFACTURY_VERSION "Alpha v1.0"
//#endif
#define MANUFACTURY_VERSION "1.0 TEST"

//#define COLOR1 1

//File actions
void FileNew(void) { log_debug("FileNew"); };

void FileOpen(void) { log_debug("FileOpen"); };

void FileSave(void) { log_debug("FileSave"); };

void FileSaveAs(void) { log_debug("FileSaveAs"); };

//Edit actions
void EditFind(void) { log_debug("EditFind"); };

void EditAdd(void) { log_debug("EditAdd"); };

void EditDelete(void) {log_debug("EditDelete");};

void EditChange(void) {log_debug("EditChange");};

//Tools actions
void ToolsExportCSV(void) {log_debug("ToolsExportCSV");};

void ToolsCreateReport(void) {log_debug("ToolsCreateReport");};

void TestS(void) {
    mvaddstr(11, 1, "SAVE   ");
}

void TestC(void) {
    mvaddstr(11, 1, "COPY   ");
}

void TestV(void) {
    mvaddstr(11, 1, "PASTE  ");
}

void EventHandler(HotKey* h) {
    mvprintw(12, 1, "Event: %c %d          ", h->key, h->modifiers);
}

void ButtonAct(void) {
    log_debug("Button clicked");
}

int main() {
    FILE* log = fopen("test.txt", "w");
    log_set_fp(log);

    //инициализация главного окна
    initscr();
    //режим распознавания каждого нажатия клавиши без ожадания Enter
    cbreak();
    //отключение отображения введенного символа
    noecho();
    //отключение курсора
    curs_set(0);
    //неблокирующий ввод
    nodelay(stdscr, TRUE);
    //распознавание функциональных кнопок клавиатуры(F1, ...)
    keypad(stdscr, TRUE);
    //сохранение модификаторов нажатых клавиш при чтении(Ctrl, Alt, Shift, ...)
    PDC_save_key_modifiers(TRUE);
    //поддержка цвета
    start_color();
    //поддержка мыши
    mouse_set(ALL_MOUSE_EVENTS);

    PDC_set_title("Manufactury v" MANUFACTURY_VERSION);

    InitStyle();
    InitHotKeyHandler(EventHandler);

    init_pair(250, COLOR_BLACK, COLOR_WHITE);


    RegisterHotKeyAction(CreateHotKey('A', KEY_CTRL | KEY_SHIFT), TestS);
    RegisterHotKeyAction(CreateHotKey('C', KEY_CTRL), TestC);
    RegisterHotKeyAction(CreateHotKey('Z', KEY_CTRL), TestV);;

    log_debug("ENTER %d", KEY_ENTER);

    Layout* mainLayout = CreateLayout(0, 0, 80, 24);
    wbkgd(panel_window(mainLayout->layoutPanel), COLOR_PAIR(250) | L' ');


    Component* button = CreateButton(buttonStyle, 1, 8, 10, L"Test ёЁ bel", ButtonAct);
    ButtonSetEnabled(button, false);
    Component* edit = CreateEdit(editStyle, 15, 8, 7);
    Component* edit2 = CreateEdit(editStyle, 27, 8, 4);
    LayoutAddComponent(mainLayout, button);
    LayoutAddComponent(mainLayout, edit);
    LayoutAddComponent(mainLayout, edit2);

    Component* menu1 = CreateMenu(menuStyle, 0, 15, L"Файл", 4,
                                  L"Новый", CreateHotKey('N', KEY_CTRL), FileNew,
                                  L"Открыть", CreateHotKey('O', KEY_CTRL), FileOpen,
                                  L"Сохранить", CreateHotKey('S', KEY_CTRL), FileSave,
                                  L"Сохранить как...", CreateHotKey('S', KEY_CTRL | KEY_SHIFT), FileSaveAs);
    Component* menu2 = CreateMenu(menuStyle, 6, 15, L"Правка", 4,
                                  L"Найти", CreateHotKey('F', KEY_CTRL), EditFind,
                                  L"Добавить", CreateHotKey('I', KEY_CTRL), EditAdd,
                                  L"Удалить", CreateHotKey('D', KEY_CTRL), EditDelete,
                                  L"Изменить", CreateHotKey('E', KEY_CTRL), EditChange);
    Component* menu3 = CreateMenu(menuStyle, 14, 15, L"Инструменты", 2,
                                  L"Экспорт в .CSV", CreateHotKey('E', KEY_CTRL | KEY_ALT | KEY_SHIFT), ToolsExportCSV,
                                  L"Создать отчет", CreateHotKey('R', KEY_CTRL), ToolsCreateReport);
    LayoutAddComponent(mainLayout, menu1);
    LayoutAddComponent(mainLayout, menu2);
    LayoutAddComponent(mainLayout, menu3);

    SetMainLayout(mainLayout);


    Layout* dialog = CreateLayout(5, 5, 16, 5);
    Component* de = CreateEdit(editStyle, 6, 9, 12);
    LayoutAddComponent(dialog, de);
    Component* dl = CreateLabel(labelStyle, 6, 7, 12, L"Test dialog");
    LayoutAddComponent(dialog, dl);

    ActivateLayout(dialog);

    update_panels();
    doupdate();

    MEVENT event;
    int input = getch();
    while (input != KEY_F(3)) {
        input = getch();
        if (input != ERR) {
            unsigned long modifiers = PDC_get_key_modifiers();
            if (input == KEY_RESIZE) {
                log_debug("RESIZE!!!!!!!");
                resize_term(24, 80);
            }
            if (input == KEY_MOUSE) {
                nc_getmouse(&event);
                LayoutHandleMouseEvent(event);
            } else {
                if (!HandleHotKeyEvent(input, modifiers)) {
                    LayoutHandleKeyboardEvent(input, modifiers);
                }
            }
            if (input == KEY_F(4)) {
                ActivateLayout(NULL);
            }
            update_panels();
            doupdate();
        }
    }

    //завершение работы curses
    endwin();
    fclose(log);
}