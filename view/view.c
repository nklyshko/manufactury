#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include <minmax.h>
#include <data_types.h>
#include "styles.h"
#include "view_contract.h"
#include "winapi_bridge.h"
#include "logo.h"

#define MANUFACTURY_VERSION "0.5 Beta"

#define HEIGHT 30
#define WIDTH 115

#define LOGO_Y 10
#define VERSION_Y 17
#define HELP_Y 19

#define MAX_TABLE_SIZE 23
#define TABLE_WIDTH WIDTH - 1
#define COLUMNS_COUNT 12
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

Layout* mainLayout;
Component* scrollBar;
Component* labels[COLUMNS_COUNT] = {0};
Component** columns[COLUMNS_COUNT] = {0};

Component* idColLabel;
Component* colId[MAX_TABLE_SIZE];
Component* surnameColLabel;
Component* colSurname[MAX_TABLE_SIZE];
Component* nameColLabel;
Component* colName[MAX_TABLE_SIZE];
Component* patronymicColLabel;
Component* colPatronymic[MAX_TABLE_SIZE];
Component* yobColLabel;
Component* colYOB[MAX_TABLE_SIZE];
Component* genderColLabel;
Component* colGender[MAX_TABLE_SIZE];
Component* profColLabel;
Component* colProf[MAX_TABLE_SIZE];
Component* expColLabel;
Component* colExp[MAX_TABLE_SIZE];
Component* classColLabel;
Component* colClass[MAX_TABLE_SIZE];
Component* deptColLabel;
Component* colDept[MAX_TABLE_SIZE];
Component* plotColLabel;
Component* colPlot[MAX_TABLE_SIZE];
Component* salaryColLabel;
Component* colSalary[MAX_TABLE_SIZE];

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
int currentTableSize = 0;
Array* currentData = NULL;
int currentPos = 0;

void OnColumnDirectionChange(Component* handle) {
    for (int i = 0; i < COLUMNS_COUNT; i++) {
        if (labels[i] != NULL && labels[i] != handle) {
            ColumnLabelSetDirection(labels[i], NONE);
        }
    }
    //TODO: sort using comparator from handle.custom
}

void OnIdButtonClick(Component* handle) {
    log_debug("Click");
}

void createIdCol() {
    idColLabel = CreateColumnLabel(columnLabelStyle,
            COL_ID_X, TABLE_LABEL_Y, COL_ID_WIDTH, L"Т/Н");
    labels[0] = idColLabel;
    columns[0] = colId;
    ColumnLabel* columnLabel = idColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, idColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colId[i] = CreateButton(i % 2 == 0 ? evenButtonStyle : oddButtonStyle,
                COL_ID_X, TABLE_BODY_START_Y + i, COL_ID_WIDTH, L"", OnIdButtonClick);
    }
}

void createSurnameCol() {
    surnameColLabel = CreateColumnLabel(columnLabelStyle,
            COL_SURNAME_X, TABLE_LABEL_Y, COL_SURNAME_WIDTH, L"Фамилия");
    labels[1] = surnameColLabel;
    columns[1] = colSurname;
    ColumnLabel* columnLabel = surnameColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, surnameColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colSurname[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_SURNAME_X, TABLE_BODY_START_Y + i, COL_SURNAME_WIDTH - 1);
        colSurname[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colSurname[i]);
    }
}

void createNameCol() {
    nameColLabel = CreateColumnLabel(columnLabelStyle,
            COL_NAME_X, TABLE_LABEL_Y, COL_NAME_WIDTH, L"Имя");
    labels[2] = nameColLabel;
    columns[2] = colName;
    ColumnLabel* columnLabel = nameColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, nameColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colName[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_NAME_X, TABLE_BODY_START_Y + i, COL_NAME_WIDTH - 1);
        colName[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colName[i]);
    }
}

void createPatronymicCol() {
    patronymicColLabel = CreateColumnLabel(columnLabelStyle,
            COL_PATRONYMIC_X, TABLE_LABEL_Y, COL_PATRONYMIC_WIDTH, L"Отчество");
    labels[3] = patronymicColLabel;
    columns[3] = colPatronymic;
    ColumnLabel* columnLabel = patronymicColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, patronymicColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colPatronymic[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_PATRONYMIC_X, TABLE_BODY_START_Y + i, COL_PATRONYMIC_WIDTH - 1);
        colPatronymic[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colPatronymic[i]);
    }
}

void createYOBCol() {
    yobColLabel = CreateColumnLabel(columnLabelStyle,
            COL_YOB_X, TABLE_LABEL_Y, COL_YOB_WIDTH, L"Г.р.");
    labels[4] = yobColLabel;
    columns[4] = colYOB;
    ColumnLabel* columnLabel = yobColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, yobColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colYOB[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_YOB_X, TABLE_BODY_START_Y + i, COL_YOB_WIDTH - 1);
        colYOB[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colYOB[i]);
    }
}

void createGenderCol() {
    genderColLabel = CreateColumnLabel(columnLabelStyle,
            COL_GENDER_X, TABLE_LABEL_Y, COL_GENDER_WIDTH, L"Пол");
    labels[5] = genderColLabel;
    columns[5] = colGender;
    ColumnLabel* columnLabel = genderColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, genderColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colGender[i] = CreateSelect(i % 2 == 0 ? evenSelectStyle : oddSelectStyle,
                COL_GENDER_X, TABLE_BODY_START_Y + i, COL_GENDER_WIDTH, 2, L"М", L"Ж");
        colGender[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colGender[i]);
    }
}

void createProfCol() {
    profColLabel = CreateColumnLabel(columnLabelStyle,
            COL_PROF_X, TABLE_LABEL_Y, COL_PROF_WIDTH, L"Профессия");
    labels[6] = profColLabel;
    columns[6] = colProf;
    ColumnLabel* columnLabel = profColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, profColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colProf[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_PROF_X, TABLE_BODY_START_Y + i, COL_PROF_WIDTH - 1);
        colProf[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colProf[i]);
    }
}

void createExpCol() {
    expColLabel = CreateColumnLabel(columnLabelStyle,
            COL_EXP_X, TABLE_LABEL_Y, COL_EXP_WIDTH, L"Оп.");
    labels[7] = expColLabel;
    columns[7] = colExp;
    ColumnLabel* columnLabel = expColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, expColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colExp[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_EXP_X, TABLE_BODY_START_Y + i, COL_EXP_WIDTH - 1);
        colExp[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colExp[i]);
    }
}

void createClassCol() {
    classColLabel = CreateColumnLabel(columnLabelStyle,
            COL_CLASS_X, TABLE_LABEL_Y, COL_CLASS_WIDTH, L"Р-д");
    labels[8] = classColLabel;
    columns[8] = colClass;
    ColumnLabel* columnLabel = classColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, classColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colClass[i] = CreateSelect(i % 2 == 0 ? evenSelectStyle : oddSelectStyle,
                COL_CLASS_X, TABLE_BODY_START_Y + i, COL_CLASS_WIDTH, 3, L"1", L"2", L"3");
        colClass[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colClass[i]);
    }
}

void createDeptCol() {
    deptColLabel = CreateColumnLabel(columnLabelStyle,
            COL_DEPT_X, TABLE_LABEL_Y, COL_DEPT_WIDTH, L"Цех");
    labels[9] = deptColLabel;
    columns[9] = colDept;
    ColumnLabel* columnLabel = deptColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, deptColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colDept[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_DEPT_X, TABLE_BODY_START_Y + i, COL_DEPT_WIDTH - 1);
        colDept[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colDept[i]);
    }
}

void createPlotCol() {
    plotColLabel = CreateColumnLabel(columnLabelStyle,
            COL_PLOT_X, TABLE_LABEL_Y, COL_PLOT_WIDTH, L"Уч.");
    labels[10] = plotColLabel;
    columns[10] = colPlot;
    ColumnLabel* columnLabel = plotColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, plotColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colPlot[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_PLOT_X, TABLE_BODY_START_Y + i, COL_PLOT_WIDTH - 1);
        colPlot[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colPlot[i]);
    }
}

void createSalaryCol() {
    salaryColLabel = CreateColumnLabel(columnLabelStyle,
            COL_SALARY_X, TABLE_LABEL_Y, COL_SALARY_WIDTH, L"Зарплата");
    labels[11] = salaryColLabel;
    columns[11] = colSalary;
    ColumnLabel* columnLabel = salaryColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, salaryColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colSalary[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_SALARY_X, TABLE_BODY_START_Y + i, COL_SALARY_WIDTH - 1);
        colSalary[i]->tabFocusing = false;
        LayoutAddComponent(mainLayout, colSalary[i]);
    }
}

void hideLines(int begin) {
    for (int l = begin; l < MAX_TABLE_SIZE; l++) {
        for (int c = 0; c < COLUMNS_COUNT; c++) {
            HideComponent(columns[c][l]);
        }
    }
}

void showLines(int begin, int count) {
    for (int l = begin; l < begin + count; l++) {
        for (int c = 0; c < COLUMNS_COUNT; c++) {
            ShowComponent(columns[c][l]);
        }
    }
}

void enableLabels(bool enabled) {
    for (int c = 0; c < COLUMNS_COUNT; c++) {
        ColumnLabelSetEnabled(labels[c], enabled);
    }
}

void drawTableHeader(bool disabled) {
    WINDOW* w = mainLayout->window;
    mvwchgat(w, 0, 0, WIDTH, 0, (short) menuStyle->defaultLabel, NULL);
    wattrset(w, COLOR_PAIR(disabled ? transitionMenuTableDisabled : transitionMenuTable));
    mvwhline(w, TABLE_LABEL_Y - 1, 0, ACS_BBLOCK, WIDTH);
    wattrset(w, COLOR_PAIR(disabled ? transitionMenuTableDisabled : transitionMenuTable));
    mvwhline(w, TABLE_LABEL_Y + 1, 0, ACS_BLOCK, WIDTH);
    wattrset(w, COLOR_PAIR(disabled ? tableDisabledColor : tableEvenColor));
    mvwaddch(w, TABLE_LABEL_Y, WIDTH - 2, ACS_RBLOCK);
    mvwaddch(w, TABLE_LABEL_Y, WIDTH - 1, ACS_BLOCK);
    for (int c = 0; c < COLUMNS_COUNT; c++) {
        int x = getbegx(((ColumnLabel*) labels[c]->spec)->panel->window) - 1;
        mvwaddch(w, TABLE_LABEL_Y, x, ACS_LBLOCK);
    }
}

void drawTableBody() {
    WINDOW* w = mainLayout->window;
    for (int l = 0; l < MAX_TABLE_SIZE; l++) {
        if (l < currentTableSize) {
            wattrset(w, COLOR_PAIR(l % 2 == 0 ? tableEvenColor : tableOddColor));
        } else {
            wattrset(w, COLOR_PAIR(tableEvenColor));
        }
        mvwaddch(w, TABLE_BODY_START_Y + l, WIDTH - 2, ACS_RBLOCK);
        for (int c = 0; c < COLUMNS_COUNT; c++) {
            int x = getbegx(((ColumnLabel*) labels[c]->spec)->panel->window) - 1;
            mvwaddch(w, TABLE_BODY_START_Y + l, x, ACS_LBLOCK);
        }
    }
}

void drawStarter() {
    WINDOW* w = mainLayout->window;
    wattrset(w, 0);
    int x = ((int) (WIDTH - wcslen(logo[0]))) / 2;
    for (int i = 0; i < LOGO_SIZE;i++) {
        mvwaddwstr(w, LOGO_Y + i, x, logo[i]);
    }
    mvwaddstr(w, VERSION_Y, (WIDTH - 17) / 2, "Manufactury v" MANUFACTURY_VERSION);
    mvwaddstr(w, HELP_Y, (WIDTH - 69) / 2, "Для начала работы откройте файл(Ctrl+O) или создайте новый(Ctrl+N)...");
}

void drawTableFooter(bool disabled) {
    WINDOW* w = mainLayout->window;
    wattrset(w, COLOR_PAIR(disabled ? transitionMenuTableDisabled : transitionMenuTable));
    mvwhline(w, TABLE_BODY_START_Y + MAX_TABLE_SIZE, 0, ACS_UBLOCK, WIDTH);
}

void drawMainLayout() {

}

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

    resize_term(HEIGHT, WIDTH);

    InitStyle();
    InitHotKeyHandler(NULL);

    mainLayout = CreateLayout(0, 0, WIDTH, HEIGHT);
    wbkgd(mainLayout->window, COLOR_PAIR(mainBackground));

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
    for (int l = 0; l < MAX_TABLE_SIZE; l++) {
        LayoutAddComponent(mainLayout, colId[l]);
    }

    scrollBar = CreateScrollBar(scrollBarStyle, WIDTH - 1, TABLE_BODY_START_Y, MAX_TABLE_SIZE, mainLayout);
    LayoutAddComponent(mainLayout, scrollBar);

    InitLayouts(mainLayout);
    enableLabels(false);
    HideComponent(scrollBar);
    for (int c = 0; c < COLUMNS_COUNT; c++) {
        for (int l = 0; l < MAX_TABLE_SIZE; l++) {
            HideComponent(columns[c][l]);
        }
    }

    drawTableHeader(true);
    drawStarter();
    drawTableFooter(true);

    update_panels();
    doupdate();
}

void DestroyView(void) {
    //завершение работы curses
    endwin();
}

void StartControl(void) {
    MEVENT event;
    int input;
    while (running) {
        input = getch();
        if (input != ERR) {
            unsigned long modifiers = PDC_get_key_modifiers();
            if (input == KEY_RESIZE) {
                resize_term(0, 0);
                if (LINES < HEIGHT || COLS < WIDTH) {
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
}

void SetData(Array* data, int pos) {
    currentData = data;
    currentPos = pos;
    int newSize = min((int) (array_size(currentData) - currentPos), MAX_TABLE_SIZE);
    if (newSize > currentTableSize) {
        showLines(currentTableSize, newSize - currentTableSize);
    } else {
        hideLines(newSize);
    }
    currentTableSize = newSize;
    for (int l = pos; l < pos + currentTableSize; l++) {
        Employee* employee;
        array_get_at(data, (size_t) l, (void**) &employee);
        wchar_t id[COL_ID_WIDTH];
        swprintf(id, COL_ID_WIDTH, L"%d", employee->id);
        ButtonSetText(colId[l], id);
        EditSetValue(colSurname[l], employee->surname);
        EditSetValue(colName[l], employee->name);
        EditSetValue(colPatronymic[l], employee->patronymic);
        wchar_t yob[COL_YOB_WIDTH];
        swprintf(yob, COL_YOB_WIDTH, L"%d", employee->yearOfBirth);
        EditSetValue(colYOB[l], yob);
        SelectSetValue(colGender[l], employee->gender ? 1 : 0);
        EditSetValue(colProf[l], employee->profession);
        wchar_t exp[COL_EXP_WIDTH];
        swprintf(exp, COL_EXP_WIDTH, L"%d", employee->experience);
        EditSetValue(colExp[l], exp);
        SelectSetValue(colClass[l], employee->class - 1);
        wchar_t dept[COL_DEPT_WIDTH];
        swprintf(dept, COL_DEPT_WIDTH, L"%d", employee->departmentId);
        EditSetValue(colDept[l], dept);
        wchar_t plot[COL_PLOT_WIDTH];
        swprintf(plot, COL_PLOT_WIDTH, L"%d", employee->plotId);
        EditSetValue(colPlot[l], plot);
        wchar_t salary[COL_SALARY_WIDTH];
        swprintf(salary, COL_SALARY_WIDTH, L"%d", employee->salary);
        EditSetValue(colSalary[l], salary);
    }
    ScrollBarSetCount(scrollBar, (int) array_size(data));
    ScrollBarSetNumber(scrollBar, pos);
}

void ShowTable(Array* data, int pos) {
    if (currentData == NULL) {
        if (data != NULL) {
            wclear(mainLayout->window);
            enableLabels(true);
            ShowComponent(scrollBar);
            SetData(data, pos);
            drawTableHeader(data == NULL);
            //set size to draw body properly ----> show data
            drawTableBody();
            drawTableFooter(data == NULL);
        }
    } else {
        if (data == NULL) {
            wclear(mainLayout->window);
            enableLabels(false);
            HideComponent(scrollBar);
            //hide lines
            drawTableHeader(data == NULL);
            drawStarter();
            drawTableFooter(data == NULL);
        } else {
            SetData(data, pos);
            drawTableBody();
        }
    }

    update_panels();
    doupdate();
}

void FileOpen(void) {

}

//File actions
void FileNew(void) {};

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