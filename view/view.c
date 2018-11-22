#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include "styles.h"
#include "view_contract.h"
#include "winapi_bridge.h"


#define MANUFACTURY_VERSION "0.5 Beta"

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

bool running = true;

void InitView(void) {
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
    //установка заголовка окна программы
    PDC_set_title("Manufactury v" MANUFACTURY_VERSION);

    resize_term(25, 80);

    InitStyle();
    InitHotKeyHandler(NULL);

    init_pair(250, COLOR_BLACK, COLOR_WHITE);

    Layout* mainLayout = CreateLayout(0, 0, 80, 25);
    wbkgd(panel_window(mainLayout->panel), COLOR_PAIR(250) | L' ');
    mvwchgat(panel_window(mainLayout->panel), 0, 25, 80 - 25, 0, (short) menuStyle->defaultLabel, NULL);

    Component* menu1 = CreateMenu(menuStyle, 0, 0, L"Файл", 4,
                                  L"Новый", CreateHotKey('N', KEY_CTRL), FileNew,
                                  L"Открыть", CreateHotKey('O', KEY_CTRL), FileOpen,
                                  L"Сохранить", CreateHotKey('S', KEY_CTRL), FileSave,
                                  L"Сохранить как...", CreateHotKey('S', KEY_CTRL | KEY_SHIFT), FileSaveAs);
    Component* menu2 = CreateMenu(menuStyle, 6, 0, L"Правка", 4,
                                  L"Найти", CreateHotKey('F', KEY_CTRL), EditFind,
                                  L"Добавить", CreateHotKey('I', KEY_CTRL), EditAdd,
                                  L"Удалить", CreateHotKey('D', KEY_CTRL), EditDelete,
                                  L"Изменить", CreateHotKey('E', KEY_CTRL), EditChange);
    Component* menu3 = CreateMenu(menuStyle, 14, 0, L"Инструменты", 2,
                                  L"Экспорт в .CSV", CreateHotKey('E', KEY_CTRL | KEY_ALT | KEY_SHIFT), ToolsExportCSV,
                                  L"Создать отчет", CreateHotKey('R', KEY_CTRL), ToolsCreateReport);
    LayoutAddComponent(mainLayout, menu1);
    LayoutAddComponent(mainLayout, menu2);
    LayoutAddComponent(mainLayout, menu3);

    InitLayouts(mainLayout);

    update_panels();
    doupdate();

    MEVENT event;
    int input = getch();
    while (running) {
        input = getch();
        if (input != ERR) {
            unsigned long modifiers = PDC_get_key_modifiers();
            if (input == KEY_RESIZE) {
                resize_term(0, 0);
                if (LINES < 25 || COLS < 80) {
                    ShowMessage(L"Уменьшение окна не поддерживается");
                    running = false;
                    return;
                }
                resize_term(25, 80);
                PANEL* panel = stack_top_panel();
                while (panel != NULL) {
                    touchwin(panel_window(panel));
                    panel = panel_below(panel);
                }
            } else if (input == KEY_MOUSE) {
                nc_getmouse(&event);
                LayoutHandleMouseEvent(event);
            } else {
                if (!HandleHotKeyEvent(input, modifiers)) {
                    LayoutHandleKeyboardEvent(input, modifiers);
                }
            }
            update_panels();
            doupdate();
        }
    }

    //завершение работы curses
    endwin();
}

//File actions
void FileNew(void) {};

void FileOpen(void) {};

void FileSave(void) {};

void FileSaveAs(void) {};

//Edit actions
void EditFind(void) {};

void EditAdd(void) {};

void EditDelete(void) {};

void EditChange(void) {};

//Tools actions
void ToolsExportCSV(void) {};

void ToolsCreateReport(void) {};