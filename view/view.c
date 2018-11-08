#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include "styles.h"
#include "view_contract.h"
#include "menu_view.h"
#include "mouse_handler.h"


PANEL* title;
PANEL* table;
PANEL* status;

//Init
void initMenu(void);

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
    PDC_save_key_modifiers(FALSE);
    //поддержка цвета
    start_color();
    //поддержка мыши
    mouse_set(ALL_MOUSE_EVENTS);
    //размеры консоли
    resize_term(TERMINAL_HEIGHT, TERMINAL_WIDTH);

    AllocateMenus(3);
    CreateMenu(0, L"Файл", 4,
            L"Новый", CreateHotKey('N', KEY_CTRL), FileNew,
            L"Открыть", CreateHotKey('O', KEY_CTRL), FileOpen,
            L"Сохранить", CreateHotKey('S', KEY_CTRL), FileSave,
            L"Сохранить как...", CreateHotKey('S', KEY_CTRL | KEY_SHIFT), FileSaveAs);
    CreateMenu(1, L"Правка", 4,
            L"Найти", CreateHotKey('F', KEY_CTRL), EditFind,
            L"Добавить", CreateHotKey('I', KEY_CTRL), EditAdd,
            L"Удалить", CreateHotKey('D', KEY_CTRL), EditDelete,
            L"Изменить", CreateHotKey('E', KEY_CTRL), EditChange);
    CreateMenu(2, L"Инструменты", 2,
            L"Экспорт в .CSV", CreateHotKey('E', KEY_CTRL | KEY_ALT | KEY_SHIFT), ToolsExportCSV,
            L"Создать отчет", CreateHotKey('R', KEY_CTRL), ToolsCreateReport);

    InitStyle();
    InitMenu();

    update_panels();
    doupdate();

    MEVENT event;
    move(0 ,0);
    int input = ERR;
    while (input != KEY_F(3)) {
        input = getch();
        if (input != ERR) {

            if (input == KEY_MOUSE) {
                nc_getmouse(&event);
                //log_debug("MOUSE EVENT %d %d", event.y, event.x);
                handleEvent(event);
            }
            update_panels();
            doupdate();
            move(0, 0);
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