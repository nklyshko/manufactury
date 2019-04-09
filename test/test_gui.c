#include <curses.h>
#include <panel.h>
#include <minwindef.h>
#include <array.h>
#include <main/main_presenter.h>
#include <tui/component/edit.h>

#include "src/log.h"
#include "view/hotkey.h"

//#ifndef MANUFACTURY_VERSION
//#define MANUFACTURY_VERSION "Alpha v1.0"
//#endif
#define MANUFACTURY_VERSION "1.0 TEST"

//#define COLOR1 1

//File actions
void FileNew(void) { log_debug("FileNew"); };

void FileOpen(void) {
    log_debug("FileOpen");
    char fileName[MAX_PATH] = {0};
    ShowOpenFileDialog(fileName, MAX_PATH);
};

void FileSave(void) { log_debug("FileSave"); };

void FileSaveAs(void) { log_debug("FileSaveAs"); };

//Edit actions
void EditFind(void) { log_debug("EditFind"); };

void EditAdd(void) { log_debug("EditAdd"); };

void EditDelete(void) {log_debug("EditDelete");};

void EditChange(void) {log_debug("EditChange");};

//Tools actions
void ToolsExportCSV(void) {log_debug("ToolsExportCSV");}

void EntryAdded(Employee* e) {

}

void ToolsCreateReport(void) {log_debug("ToolsCreateReport");};

void EventHandler(HotKey* h) {
    //mvprintw(12, 1, "Event: %c %d          ", h->key, h->modifiers);
}

void ButtonAct(Component* handle) {
    log_debug("Button clicked");
}

Component* scrollbar;

int parseI(const wchar_t* s) {
    int num = 0;
    int i = 0;
    while(s[i] != L'\0') {
        if (s[i] < 48 || s[i] > 57) return 0;
        num = num * 10 + (s[i] - 48);
        i++;
    }
    return num;
}

void SetNum(Component* handle) {
    Edit* e = handle->spec;
    int num = parseI(e->value);
//    log_debug("SETNUM %d", num);
    ScrollBarSetNumber(scrollbar, num);
}

void SetCnt(Component* handle) {
    Edit* e = handle->spec;
    int cnt = parseI(e->value);
//    log_debug("SETCNT %d", cnt);
    ScrollBarSetCount(scrollbar, cnt);
    EditSetEnabled(handle, false);
}

void SelectedEvent(Component* handle) {
    log_debug("Selected event");
}

void SetWindowSize(int width, int height) {
    //resize_term(0, 0);
    resize_term(height, width);
    PANEL* panel = panel_below(NULL);
    while (panel != NULL) {
        touchwin(panel_window(panel));
        panel = panel_below(panel);
    }
    update_panels();
    doupdate();
}

void scrollUp(ScrollType type) {
    log_debug("SCROLL UP %d", type);
}

void scrollDown(ScrollType type) {
    log_debug("SCROLL DOWN %d", type);
}

int mainGUI(int argc, char **argv) {
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

    log_debug("ARGC %d", argc);

    if (argc > 1) {
        log_debug("OPEN WITH: %s", argv[1]);
    }

    resize_term(25, 80);

    InitStyle();
    InitHotKeyHandler(EventHandler);

    init_pair(250, COLOR_BLACK, COLOR_WHITE);

    Layout* mainLayout = CreateLayout(0, 0, 80, 25);
    wbkgd(panel_window(mainLayout->panel), COLOR_PAIR(250) | L' ');

    Component* button = CreateButton(evenButtonStyle, 1, 8, 10, L"Test ёЁ belmandsabhbsadbhb", ButtonAct);
    ButtonSetEnabled(button, false);
    Component* edit = CreateEdit(evenEditStyle, 15, 8, 7);
    EditSetValue(edit, L"90");
    EditSetEnterAction(edit, SetCnt);
    Component* edit2 = CreateEdit(evenEditStyle, 27, 8, 4);
    EditSetEnterAction(edit2, SetNum);
    scrollbar = CreateScrollBar(scrollBarStyle, 79, 1, 23, mainLayout);
    Component* select = CreateSelect(evenSelectStyle, 50, 8, 4, 3, L"М", L"Ж", L"Тест");
    select->tabFocusing = false;
    LayoutAddComponent(mainLayout, button);
    LayoutAddComponent(mainLayout, edit);
    LayoutAddComponent(mainLayout, edit2);
    LayoutAddComponent(mainLayout, select);
    LayoutAddComponent(mainLayout, scrollbar);

    Component* columnLabel = CreateColumnLabel(columnLabelStyle, 60, 8, 6, L"Test");
    LayoutAddComponent(mainLayout, columnLabel);

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

    mainLayout->OnScrollUp = scrollUp;
    mainLayout->OnScrollDown = scrollDown;

    InitLayouts(mainLayout);

    Layout* dialog = CreateLayout(5, 5, 16, 5);
    Component* de = CreateEdit(evenEditStyle, 6, 9, 12);
    LayoutAddComponent(dialog, de);
    Component* dl = CreateLabel(labelStyle, 6, 7, 12, L"Test dialog");
    LayoutAddComponent(dialog, dl);

    ActivateLayout(dialog);

    update_panels();
    doupdate();

    MEVENT event;
    int input = ERR;
    while (input != KEY_F(3)) {
        input = getch();
        if (input != ERR) {
            unsigned long modifiers = PDC_get_key_modifiers();
            if (input == KEY_RESIZE) {
                resize_term(0, 0);
                if (LINES < 25 || COLS < 80) {
                    //TODO: terminate program
                    return 0;
                }
                log_debug("%d %d", LINES, COLS);
                SetWindowSize(80, 25);
            }
            if (input == KEY_MOUSE) {
                nc_getmouse(&event);
                LayoutHandleMouseEvent(event);
            } else {
                log_debug("Keyboard %d %d", input, modifiers);
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
}