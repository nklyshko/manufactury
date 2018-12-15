#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include <minmax.h>
#include <model/data_types.h>
#include <model/filter.h>
#include <tui/layout.h>
#include <tui/styles.h>
#include <tui/hotkey.h>
#include <tui/dialog.h>
#include <tui/winapi_bridge.h>
#include <version.h>
#include "main_view.h"
#include "main_presenter.h"
#include "edit/edit_view.h"
#include "logo.h"

#define HEIGHT 30
#define WIDTH 115

#define LOGO_Y 10
#define VERSION_Y 17
#define HELP_Y 19

#define MAX_TABLE_SIZE 23
#define COLUMNS_COUNT FIELDS_COUNT
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
    ColumnLabel* columnLabel = handle->spec;
    SortData(columnLabel->fieldId, columnLabel->activeDirection);
}

void createIdCol() {
    idColLabel = CreateColumnLabel(columnLabelStyle,
            COL_ID_X, TABLE_LABEL_Y, COL_ID_WIDTH, FIELD_ID, L"Т/Н");
    labels[FIELD_ID] = idColLabel;
    columns[FIELD_ID] = colId;
    ColumnLabel* columnLabel = idColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, idColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colId[i] = CreateButton(i % 2 == 0 ? evenButtonStyle : oddButtonStyle,
                COL_ID_X, TABLE_BODY_START_Y + i, COL_ID_WIDTH, L"", EditEntry);
        colId[i]->OnKeyClick = OnIdButtonKeyClick;
        ((Button*) colId[i]->spec)->panel->OnMouseClick = OnIdButtonMouseClick;
    }
}

void createSurnameCol() {
    surnameColLabel = CreateColumnLabel(columnLabelStyle,
            COL_SURNAME_X, TABLE_LABEL_Y, COL_SURNAME_WIDTH, FIELD_SURNAME, L"Фамилия");
    labels[FIELD_SURNAME] = surnameColLabel;
    columns[FIELD_SURNAME] = colSurname;
    ColumnLabel* columnLabel = surnameColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, surnameColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colSurname[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_SURNAME_X, TABLE_BODY_START_Y + i, COL_SURNAME_WIDTH - 1);
        colSurname[i]->tabFocusing = false;
        EditSetEnterAction(colSurname[i], ChangeSurname);
        LayoutAddComponent(mainLayout, colSurname[i]);
    }
}

void createNameCol() {
    nameColLabel = CreateColumnLabel(columnLabelStyle,
            COL_NAME_X, TABLE_LABEL_Y, COL_NAME_WIDTH, FIELD_NAME, L"Имя");
    labels[FIELD_NAME] = nameColLabel;
    columns[FIELD_NAME] = colName;
    ColumnLabel* columnLabel = nameColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, nameColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colName[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_NAME_X, TABLE_BODY_START_Y + i, COL_NAME_WIDTH - 1);
        colName[i]->tabFocusing = false;
        EditSetEnterAction(colName[i], ChangeName);
        LayoutAddComponent(mainLayout, colName[i]);
    }
}

void createPatronymicCol() {
    patronymicColLabel = CreateColumnLabel(columnLabelStyle,
            COL_PATRONYMIC_X, TABLE_LABEL_Y, COL_PATRONYMIC_WIDTH, FIELD_PATRONYMIC, L"Отчество");
    labels[FIELD_PATRONYMIC] = patronymicColLabel;
    columns[FIELD_PATRONYMIC] = colPatronymic;
    ColumnLabel* columnLabel = patronymicColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, patronymicColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colPatronymic[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_PATRONYMIC_X, TABLE_BODY_START_Y + i, COL_PATRONYMIC_WIDTH - 1);
        colPatronymic[i]->tabFocusing = false;
        EditSetEnterAction(colPatronymic[i], ChangePatronymic);
        LayoutAddComponent(mainLayout, colPatronymic[i]);
    }
}

void createYOBCol() {
    yobColLabel = CreateColumnLabel(columnLabelStyle,
            COL_YOB_X, TABLE_LABEL_Y, COL_YOB_WIDTH, FIELD_YOB, L"Г.р.");
    labels[FIELD_YOB] = yobColLabel;
    columns[FIELD_YOB] = colYOB;
    ColumnLabel* columnLabel = yobColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, yobColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colYOB[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_YOB_X, TABLE_BODY_START_Y + i, COL_YOB_WIDTH - 1);
        colYOB[i]->tabFocusing = false;
        EditSetFilter(colYOB[i], PositiveNumberFilter);
        EditSetEnterAction(colYOB[i], ChangeYOB);
        LayoutAddComponent(mainLayout, colYOB[i]);
    }
}

void createGenderCol() {
    genderColLabel = CreateColumnLabel(columnLabelStyle,
            COL_GENDER_X, TABLE_LABEL_Y, COL_GENDER_WIDTH, FIELD_GENDER, L"Пол");
    labels[FIELD_GENDER] = genderColLabel;
    columns[FIELD_GENDER] = colGender;
    ColumnLabel* columnLabel = genderColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, genderColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colGender[i] = CreateSelect(i % 2 == 0 ? evenSelectStyle : oddSelectStyle,
                COL_GENDER_X, TABLE_BODY_START_Y + i, COL_GENDER_WIDTH, 2, L"М", L"Ж");
        colGender[i]->tabFocusing = false;
        SelectSetEnterAction(colGender[i], ChangeGender);
        LayoutAddComponent(mainLayout, colGender[i]);
    }
}

void createProfCol() {
    profColLabel = CreateColumnLabel(columnLabelStyle,
            COL_PROF_X, TABLE_LABEL_Y, COL_PROF_WIDTH, FIELD_PROFESSION, L"Профессия");
    labels[FIELD_PROFESSION] = profColLabel;
    columns[FIELD_PROFESSION] = colProf;
    ColumnLabel* columnLabel = profColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, profColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colProf[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_PROF_X, TABLE_BODY_START_Y + i, COL_PROF_WIDTH - 1);
        colProf[i]->tabFocusing = false;
        EditSetEnterAction(colProf[i], ChangeProfession);
        LayoutAddComponent(mainLayout, colProf[i]);
    }
}

void createExpCol() {
    expColLabel = CreateColumnLabel(columnLabelStyle,
            COL_EXP_X, TABLE_LABEL_Y, COL_EXP_WIDTH, FIELD_EXPERIENCE, L"Оп.");
    labels[FIELD_EXPERIENCE] = expColLabel;
    columns[FIELD_EXPERIENCE] = colExp;
    ColumnLabel* columnLabel = expColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, expColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colExp[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_EXP_X, TABLE_BODY_START_Y + i, COL_EXP_WIDTH - 1);
        colExp[i]->tabFocusing = false;
        EditSetFilter(colExp[i], PositiveNumberFilter);
        EditSetEnterAction(colExp[i], ChangeExperience);
        LayoutAddComponent(mainLayout, colExp[i]);
    }
}

void createClassCol() {
    classColLabel = CreateColumnLabel(columnLabelStyle,
            COL_CLASS_X, TABLE_LABEL_Y, COL_CLASS_WIDTH, FIELD_CLASS, L"Р-д");
    labels[FIELD_CLASS] = classColLabel;
    columns[FIELD_CLASS] = colClass;
    ColumnLabel* columnLabel = classColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, classColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colClass[i] = CreateSelect(i % 2 == 0 ? evenSelectStyle : oddSelectStyle,
                COL_CLASS_X, TABLE_BODY_START_Y + i, COL_CLASS_WIDTH, 3, L"1", L"2", L"3");
        colClass[i]->tabFocusing = false;
        SelectSetEnterAction(colClass[i], ChangeClass);
        LayoutAddComponent(mainLayout, colClass[i]);
    }
}

void createDeptCol() {
    deptColLabel = CreateColumnLabel(columnLabelStyle,
            COL_DEPT_X, TABLE_LABEL_Y, COL_DEPT_WIDTH, FIELD_DEPARTMENT, L"Цех");
    labels[FIELD_DEPARTMENT] = deptColLabel;
    columns[FIELD_DEPARTMENT] = colDept;
    ColumnLabel* columnLabel = deptColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, deptColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colDept[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_DEPT_X, TABLE_BODY_START_Y + i, COL_DEPT_WIDTH - 1);
        colDept[i]->tabFocusing = false;
        EditSetFilter(colDept[i], PositiveNumberFilter);
        EditSetEnterAction(colDept[i], ChangeDepartment);
        LayoutAddComponent(mainLayout, colDept[i]);
    }
}

void createPlotCol() {
    plotColLabel = CreateColumnLabel(columnLabelStyle,
            COL_PLOT_X, TABLE_LABEL_Y, COL_PLOT_WIDTH, FIELD_PLOT, L"Уч.");
    labels[FIELD_PLOT] = plotColLabel;
    columns[FIELD_PLOT] = colPlot;
    ColumnLabel* columnLabel = plotColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, plotColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colPlot[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_PLOT_X, TABLE_BODY_START_Y + i, COL_PLOT_WIDTH - 1);
        colPlot[i]->tabFocusing = false;
        EditSetFilter(colPlot[i], PositiveNumberFilter);
        EditSetEnterAction(colPlot[i], ChangePlot);
        LayoutAddComponent(mainLayout, colPlot[i]);
    }
}

void createSalaryCol() {
    salaryColLabel = CreateColumnLabel(columnLabelStyle,
            COL_SALARY_X, TABLE_LABEL_Y, COL_SALARY_WIDTH, FIELD_SALARY, L"Зарплата");
    labels[FIELD_SALARY] = salaryColLabel;
    columns[FIELD_SALARY] = colSalary;
    ColumnLabel* columnLabel = salaryColLabel->spec;
    columnLabel->OnDirectionChange = OnColumnDirectionChange;
    LayoutAddComponent(mainLayout, salaryColLabel);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        colSalary[i] = CreateEdit(i % 2 == 0 ? evenEditStyle : oddEditStyle,
                COL_SALARY_X, TABLE_BODY_START_Y + i, COL_SALARY_WIDTH - 1);
        colSalary[i]->tabFocusing = false;
        EditSetEnterAction(colSalary[i], ChangeSalary);
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

void showLine(int l, Employee* employee) {
    wchar_t id[COL_ID_WIDTH];
    swprintf(id, COL_ID_WIDTH, L"%d", employee->id);
    ButtonSetText(colId[l], id);
    EditSetValue(colSurname[l], employee->surname);
    EditSetValue(colName[l], employee->name);
    EditSetValue(colPatronymic[l], employee->patronymic);
    wchar_t yob[COL_YOB_WIDTH];
    swprintf(yob, COL_YOB_WIDTH, L"%d", employee->yob);
    EditSetValue(colYOB[l], yob);
    SelectSetValue(colGender[l], employee->gender ? 0 : 1);
    EditSetValue(colProf[l], employee->profession);
    wchar_t exp[COL_EXP_WIDTH];
    swprintf(exp, COL_EXP_WIDTH, L"%d", employee->experience);
    EditSetValue(colExp[l], exp);
    SelectSetValue(colClass[l], employee->class - 1);
    wchar_t dept[COL_DEPT_WIDTH];
    swprintf(dept, COL_DEPT_WIDTH, L"%d", employee->department);
    EditSetValue(colDept[l], dept);
    wchar_t plot[COL_PLOT_WIDTH];
    swprintf(plot, COL_PLOT_WIDTH, L"%d", employee->plot);
    EditSetValue(colPlot[l], plot);
    wchar_t salary[COL_SALARY_WIDTH];
    swprintf(salary, COL_SALARY_WIDTH, L"%d", employee->salary);
    EditSetValue(colSalary[l], salary);
}

void showData(int pos) {
    currentPos = pos;
    int newSize = min((int) (array_size(currentData) - currentPos), MAX_TABLE_SIZE);
    if (newSize != currentTableSize) {
        if (newSize > currentTableSize) {
            showLines(currentTableSize, newSize - currentTableSize);
        } else {
            hideLines(newSize);
        }
        currentTableSize = newSize;
        drawTableBody();
    }
    for (int l = 0; l < currentTableSize; l++) {
        Employee* employee;
        array_get_at(currentData, (size_t) pos + l, (void**) &employee);
        for (int c = 0; c < COLUMNS_COUNT; c++) {
            columns[c][l]->custom = employee;
        }
        showLine(l, employee);
    }
    ScrollBarSetNumber(scrollBar, pos);
}

void InitMainView(void) {
    resize_term(HEIGHT, WIDTH);

    mainLayout = CreateLayout(0, 0, WIDTH, HEIGHT);
    wbkgd(mainLayout->window, COLOR_PAIR(mainBackground));

    Component* menu1 = CreateMenu(menuStyle, 0, 0, L"Файл", 4,
                                  L"Новый", CreateHotKey('N', KEY_CTRL), FileNew,
                                  L"Открыть", CreateHotKey('O', KEY_CTRL), FileOpen,
                                  L"Сохранить", CreateHotKey('S', KEY_CTRL), FileSave,
                                  L"Сохранить как...", CreateHotKey('S', KEY_CTRL | KEY_SHIFT), FileSaveAs);
    Component* menu2 = CreateMenu(menuStyle, 6, 0, L"Правка", 5,
                                  L"Найти", CreateHotKey('F', KEY_CTRL), EditFind,
                                  L"Отменить поиск", CreateHotKey('F', KEY_ALT), EditCancelFind,
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

    mainLayout->OnScrollDown = TableOnScrollDown;
    mainLayout->OnScrollUp = TableOnScrollUp;

    InitLayouts(mainLayout);

    update_panels();
    doupdate();
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
                if (LINES != HEIGHT || COLS != WIDTH) {
                    ShowMessage(L"Изменение размеров окна не поддерживается");
                    running = false;
                    return;
                }
                resize_term(HEIGHT, WIDTH);
                PANEL* panel = panel_below(NULL);
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

void SetPos(int pos) {
    showData(pos);
}

void SetData(Array* data) {
    currentData = data;
    ScrollBarSetCount(scrollBar, (int) array_size(currentData));
    showData(0);
}

void ShowStarter(void) {
    enableLabels(false);
    HideComponent(scrollBar);
    hideLines(0);
    currentTableSize = 0;
    wclear(mainLayout->window);
    drawTableHeader(true);
    drawStarter();
    drawTableFooter(true);
    update_panels();
    doupdate();
}

void ShowTable(void) {
    enableLabels(true);
    ShowComponent(scrollBar);
    hideLines(0);
    currentTableSize = 0;
    wclear(mainLayout->window);
    drawTableHeader(false);
    drawTableBody();
    drawTableFooter(false);
    update_panels();
    doupdate();
}

void ResetActiveColumnLabel(void) {
    for (int i = 0; i < COLUMNS_COUNT; i++) {
        ColumnLabelSetDirection(labels[i], NONE);
    }
}

void ShowFileReadError(void) {
    ShowMessageDialog(L"Ошибка чтения файла", NULL);
}

void ShowFileWriteError(void) {
    ShowMessageDialog(L"Ошибка записи файла", NULL);
}

void ShowFilterError(void) {
    ShowMessageDialog(L"Записи не найдены", NULL);
}

void ShowEntryChanges(Employee* e) {
    for (int l = 0; l < currentTableSize; l++) {
        Employee* employee;
        array_get_at(currentData, (size_t) currentPos + l, (void**) &employee);
        if (employee == e) {
            showLine(l, employee);
            break;
        }
    }
}
