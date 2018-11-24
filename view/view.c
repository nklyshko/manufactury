#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include "styles.h"
#include "view_contract.h"
#include "winapi_bridge.h"


#define HEIGHT 30
#define WIDTH 114
#define TABLE_SIZE 23
#define MANUFACTURY_VERSION "0.5 Beta"
#define COLUMNS_COUNT 12

bool running = true;

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

#define TABLE_LABEL_Y 2
#define TABLE_BODY_START_Y TABLE_LABEL_Y + 2

#define COL_ID_X 1
#define COL_ID_WIDTH 5
#define COL_SURNAME_X COL_ID_X+1+COL_ID_WIDTH
#define COL_SURNAME_WIDTH 17
#define COL_NAME_X COL_SURNAME_X+1+COL_SURNAME_WIDTH
#define COL_NAME_WIDTH 17
#define COL_PATRONYMIC_X COL_NAME_X+1+COL_NAME_WIDTH
#define COL_PATRONYMIC_WIDTH 17
#define COL_YOB_X COL_PATRONYMIC_X+1+COL_PATRONYMIC_WIDTH
#define COL_YOB_WIDTH 5
#define COL_GENDER_X COL_YOB_X+1+COL_YOB_WIDTH
#define COL_GENDER_WIDTH 3
#define COL_PROF_X COL_GENDER_X+1+COL_GENDER_WIDTH
#define COL_PROF_WIDTH 17
#define COL_EXP_X COL_PROF_X+1+COL_PROF_WIDTH
#define COL_EXP_WIDTH 3
#define COL_CLASS_X COL_EXP_X+1+COL_EXP_WIDTH
#define COL_CLASS_WIDTH 3
#define COL_DEPT_X COL_CLASS_X+1+COL_CLASS_WIDTH
#define COL_DEPT_WIDTH 3
#define COL_PLOT_X COL_DEPT_X+1+COL_DEPT_WIDTH
#define COL_PLOT_WIDTH 3
#define COL_SALARY_X COL_PLOT_X+1+COL_PLOT_WIDTH
#define COL_SALARY_WIDTH 8


bool isColumnBorder(int x) {
    x++;
    return x == 1
        || x == COL_SURNAME_X || x == COL_NAME_X || x == COL_PATRONYMIC_X || x == COL_YOB_X || x == COL_GENDER_X
        || x == COL_PROF_X || x == COL_EXP_X || x == COL_CLASS_X || x == COL_DEPT_X || x == COL_PLOT_X || x == COL_SALARY_X;
}

Layout* mainLayout;

Component* idColLabel;
Component* colId[TABLE_SIZE];
Component* surnameColLabel;
Component* colSurname[TABLE_SIZE];
Component* nameColLabel;
Component* colName[TABLE_SIZE];
Component* patronymicColLabel;
Component* colPatronymic[TABLE_SIZE];
Component* yobColLabel;
Component* colYOB[TABLE_SIZE];
Component* genderColLabel;
Component* colGender[TABLE_SIZE];
Component* profColLabel;
Component* colProf[TABLE_SIZE];
Component* expColLabel;
Component* colExp[TABLE_SIZE];
Component* classColLabel;
Component* colClass[TABLE_SIZE];
Component* deptColLabel;
Component* colDept[TABLE_SIZE];
Component* plotColLabel;
Component* colPlot[TABLE_SIZE];
Component* salaryColLabel;
Component* colSalary[TABLE_SIZE];
Component* columns[COLUMNS_COUNT] = {0};

void OnColumnDirectionChange(Component* handle) {
    for (int i = 0; i < COLUMNS_COUNT; i++) {
        if (columns[i] != NULL && columns[i] != handle) {
            ColumnLabelSetDirection(columns[i], NONE);
        }
    }
    //TODO: sort using comparator from handle.custom
}

void changeRecordId(Component* handle) {
    log_debug("Click");
}

void createIdCol() {
    idColLabel = CreateColumnLabel(columnLabelStyle, COL_ID_X, TABLE_LABEL_Y, COL_ID_WIDTH, L"Т/Н");
    columns[0] = idColLabel;
    ColumnLabel* columnLabel = idColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, idColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colId[i] = CreateButton(i % 2 == 0 ? evenButtonStyle : oddButtonStyle, COL_ID_X, TABLE_BODY_START_Y + i, COL_ID_WIDTH, L"", changeRecordId);
    }
}

void createSurnameCol() {
    surnameColLabel = CreateColumnLabel(columnLabelStyle, COL_SURNAME_X, TABLE_LABEL_Y, COL_SURNAME_WIDTH, L"Фамилия");
    columns[1] = surnameColLabel;
    ColumnLabel* columnLabel = surnameColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, surnameColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colSurname[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_SURNAME_X, TABLE_BODY_START_Y + i, COL_SURNAME_WIDTH - 1);
        colSurname[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colSurname[i]);
    }
}

void createNameCol() {
    nameColLabel = CreateColumnLabel(columnLabelStyle, COL_NAME_X, TABLE_LABEL_Y, COL_NAME_WIDTH, L"Имя");
    columns[2] = nameColLabel;
    ColumnLabel* columnLabel = nameColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, nameColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colName[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_NAME_X, TABLE_BODY_START_Y + i, COL_NAME_WIDTH - 1);
        colName[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colName[i]);
    }
}

void createPatronymicCol() {
    patronymicColLabel = CreateColumnLabel(columnLabelStyle, COL_PATRONYMIC_X, TABLE_LABEL_Y, COL_PATRONYMIC_WIDTH, L"Отчество");
    columns[3] = patronymicColLabel;
    ColumnLabel* columnLabel = patronymicColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, patronymicColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colPatronymic[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_PATRONYMIC_X, TABLE_BODY_START_Y + i, COL_PATRONYMIC_WIDTH - 1);
        colPatronymic[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colPatronymic[i]);
    }
}

void createYOBCol() {
    yobColLabel = CreateColumnLabel(columnLabelStyle, COL_YOB_X, TABLE_LABEL_Y, COL_YOB_WIDTH, L"Г.р.");
    columns[4] = yobColLabel;
    ColumnLabel* columnLabel = yobColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, yobColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colYOB[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_YOB_X, TABLE_BODY_START_Y + i, COL_YOB_WIDTH - 1);
        colYOB[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colYOB[i]);
    }
}

void createGenderCol() {
    genderColLabel = CreateColumnLabel(columnLabelStyle, COL_GENDER_X, TABLE_LABEL_Y, COL_GENDER_WIDTH, L"Пол");
    columns[5] = genderColLabel;
    ColumnLabel* columnLabel = genderColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, genderColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colGender[i] = CreateSelect(i % 2 == 0 ? evenSelectStyle : oddSelectStyle, COL_GENDER_X, TABLE_BODY_START_Y + i, COL_GENDER_WIDTH, 2, L"М", L"Ж");
        colGender[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colGender[i]);
    }
}

void createProfCol() {
    profColLabel = CreateColumnLabel(columnLabelStyle, COL_PROF_X, TABLE_LABEL_Y, COL_PROF_WIDTH, L"Профессия");
    columns[6] = profColLabel;
    ColumnLabel* columnLabel = profColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, profColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colProf[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_PROF_X, TABLE_BODY_START_Y + i, COL_PROF_WIDTH - 1);
        colProf[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colProf[i]);
    }
}

void createExpCol() {
    expColLabel = CreateColumnLabel(columnLabelStyle, COL_EXP_X, TABLE_LABEL_Y, COL_EXP_WIDTH, L"Оп.");
    columns[7] = expColLabel;
    ColumnLabel* columnLabel = expColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, expColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colExp[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_EXP_X, TABLE_BODY_START_Y + i, COL_EXP_WIDTH - 1);
        colExp[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colExp[i]);
    }
}

void createClassCol() {
    classColLabel = CreateColumnLabel(columnLabelStyle, COL_CLASS_X, TABLE_LABEL_Y, COL_CLASS_WIDTH, L"Р-д");
    columns[8] = classColLabel;
    ColumnLabel* columnLabel = classColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, classColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colClass[i] = CreateSelect(i % 2 == 0 ? evenSelectStyle : oddSelectStyle, COL_CLASS_X, TABLE_BODY_START_Y + i, COL_CLASS_WIDTH, 3, L"1", L"2", L"3");
        colClass[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colClass[i]);
    }
}

void createDeptCol() {
    deptColLabel = CreateColumnLabel(columnLabelStyle, COL_DEPT_X, TABLE_LABEL_Y, COL_DEPT_WIDTH, L"Цех");
    columns[9] = deptColLabel;
    ColumnLabel* columnLabel = deptColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, deptColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colDept[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_DEPT_X, TABLE_BODY_START_Y + i, COL_DEPT_WIDTH - 1);
        colDept[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colDept[i]);
    }
}

void createPlotCol() {
    plotColLabel = CreateColumnLabel(columnLabelStyle, COL_PLOT_X, TABLE_LABEL_Y, COL_PLOT_WIDTH, L"Уч.");
    columns[10] = plotColLabel;
    ColumnLabel* columnLabel = plotColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, plotColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colPlot[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_PLOT_X, TABLE_BODY_START_Y + i, COL_PLOT_WIDTH - 1);
        colPlot[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colPlot[i]);
    }
}

void createSalaryCol() {
    salaryColLabel = CreateColumnLabel(columnLabelStyle, COL_SALARY_X, TABLE_LABEL_Y, COL_SALARY_WIDTH, L"Зарплата");
    columns[11] = salaryColLabel;
    ColumnLabel* columnLabel = salaryColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, salaryColLabel);
    for (int i = 0; i < TABLE_SIZE; i++) {
        colSalary[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle, COL_SALARY_X, TABLE_BODY_START_Y + i, COL_SALARY_WIDTH - 1);
        colSalary[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colSalary[i]);
    }
}


void initCurses() {
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

    resize_term(HEIGHT, WIDTH);
}

void drawMainLayout() {
    init_pair(250, COLOR_GRAY_DARK, COLOR_WHITE);
    WINDOW* w = panel_window(mainLayout->panel);
    wbkgd(w, COLOR_PAIR(250));
    mvwchgat(w, 0, 25, WIDTH - 25, 0, (short) menuStyle->defaultLabel, NULL);
    init_pair(249, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);

    wmove(w, 1, 0);
    wattrset(w, COLOR_PAIR(249));
    for (int i = 0; i < WIDTH; i++) {
        waddch(w, ACS_BBLOCK);
    }
    wattrset(w, 0);
    for (int i = 0; i < WIDTH; i++) {
        if (isColumnBorder(i)) {
            mvwaddch(w, 2, i, ACS_LBLOCK);
        }
    }
    for (int k = 4; k < TABLE_SIZE + 4; k++) {
        wmove(w, k, 0);
        if (k % 2 == 0) {
            wattrset(w, 0);
        } else {
            wattrset(w, COLOR_PAIR(249));
        }
        for (int i = 0; i < WIDTH; i++) {
            if (isColumnBorder(i)) {
                mvwaddch(w, k, i, ACS_LBLOCK);
            }
        }
    }
    wmove(w, 3, 0);
    for (int i = 0; i < WIDTH; i++) {
        waddch(w, ACS_BLOCK);
    }

//    mvwaddch(w, 2, 0, ACS_LBLOCK);
    mvwaddch(w, 2, WIDTH - 1, ACS_RBLOCK);
    for (int k = 4; k < TABLE_SIZE + 4; k++) {
        if (k % 2 == 0) {
            wattrset(w, 0);
        } else {
            wattrset(w, COLOR_PAIR(249));
        }
        mvwaddch(w, k, 0, ACS_LBLOCK);
        mvwaddch(w, k, WIDTH - 1, ACS_RBLOCK);
    }
}

void InitView(void) {
    initCurses();

    InitStyle();
    InitHotKeyHandler(NULL);

    mainLayout = CreateLayout(0, 0, WIDTH, HEIGHT);
    drawMainLayout();

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
                                  L"Экспорт в .CSV", CreateHotKey('E', KEY_CTRL | KEY_ALT), ToolsExportCSV,
                                  L"Создать отчет", CreateHotKey('R', KEY_CTRL), ToolsCreateReport);
    LayoutAddComponent(mainLayout, menu1);
    LayoutAddComponent(mainLayout, menu2);
    LayoutAddComponent(mainLayout, menu3);

    createIdCol();
    createSurnameCol();
    createNameCol();
    createPatronymicCol();
    createYOBCol();
    createGenderCol();
    createProfCol();
    createExpCol();
    createClassCol();
    createDeptCol();
    createPlotCol();
    createSalaryCol();

    for (int i = 0; i < TABLE_SIZE; i++) {
        LayoutAddComponent(mainLayout, colId[i]);
    }

    InitLayouts(mainLayout);

    update_panels();
    doupdate();

    MEVENT event;
    int input;
    while (running) {
        input = getch();
        if (input != ERR) {
            unsigned long modifiers = PDC_get_key_modifiers();
            if (input == KEY_RESIZE) {
                resize_term(0, 0);
                if (LINES < WIDTH || COLS < HEIGHT) {
                    ShowMessage(L"Уменьшение окна не поддерживается");
                    running = false;
                    return;
                }
                resize_term(HEIGHT, WIDTH);
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