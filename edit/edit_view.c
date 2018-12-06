#include <src/log.h>
#include <model/filter.h>
#include <tui/layout.h>
#include <tui/styles.h>
#include "edit_view.h"

#define DIALOG_WIDTH 38
#define DIALOG_HEIGHT 19

#define ID_INPUT_Y 1+3
#define SURNAME_INPUT_Y 2+3
#define NAME_INPUT_Y 3+3
#define PATRONYMIC_INPUT_Y 4+3
#define YOB_INPUT_Y 5+3
#define GENDER_INPUT_Y 6+3
#define PROF_INPUT_Y 7+3
#define EXP_INPUT_Y 8+3
#define CLASS_INPUT_Y 9+3
#define DEPT_INPUT_Y 10+3
#define PLOT_INPUT_Y 11+3
#define SALARY_INPUT_Y 12+3

#define ID_INPUT_WIDTH 5
#define SURNAME_INPUT_WIDTH 16
#define NAME_INPUT_WIDTH 16
#define PATRONYMIC_INPUT_WIDTH 16
#define YOB_INPUT_WIDTH 4
#define GENDER_INPUT_WIDTH 2
#define PROF_INPUT_WIDTH 16
#define EXP_INPUT_WIDTH 2
#define CLASS_INPUT_WIDTH 2
#define DEPT_INPUT_WIDTH 2
#define PLOT_INPUT_WIDTH 2
#define SALARY_INPUT_WIDTH 7

#define ID_LABEL_WIDTH 15
#define SURNAME_LABEL_WIDTH 7
#define NAME_LABEL_WIDTH 3
#define PATRONYMIC_LABEL_WIDTH 8
#define YOB_LABEL_WIDTH 12
#define GENDER_LABEL_WIDTH 3
#define PROF_LABEL_WIDTH 9
#define EXP_LABEL_WIDTH 11
#define CLASS_LABEL_WIDTH 6
#define DEPT_LABEL_WIDTH 3
#define PLOT_LABEL_WIDTH 7
#define SALARY_LABEL_WIDTH 8

#define MAX_WIDTH 16

#define INPUT_X MAX_WIDTH + 2

Layout* dialog;

Component* idEdit;
Component* surnameEdit;
Component* nameEdit;
Component* patronymicEdit;
Component* yobEdit;
Component* genderSelect;
Component* profEdit;
Component* expEdit;
Component* classSelect;
Component* deptEdit;
Component* plotEdit;
Component* salaryEdit;

Component* idLabel;
Component* surnameLabel;
Component* nameLabel;
Component* patronymicLabel;
Component* yobLabel;
Component* genderLabel;
Component* profLabel;
Component* expLabel;
Component* classLabel;
Component* deptLabel;
Component* plotLabel;
Component* salaryLabel;

Component* confirmButton;
Component* cancelButton;

Component* errorText;

int labeloffset(int x, int width) {
    return x + 1 + (MAX_WIDTH - width);
}

void (* idChangeAction)(int id);
void (* confirmAction)(void);
void (* cancelAction)(void);

void OnConfirm(Component* handle) {
    ActivateLayout(NULL);
    if (confirmAction != NULL) confirmAction();
}

void OnCancel(Component* handle) {
    ActivateLayout(NULL);
    if (cancelAction != NULL) cancelAction();
}

void OnIdEnter(Component* handle) {
    idChangeAction(GetEmployeeId());
}

void InitDataDialog(int color) {
    int x = (COLS - DIALOG_WIDTH) / 2;
    int y = (LINES - DIALOG_HEIGHT) / 2;

    dialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(dialog->window, COLOR_PAIR(color));

    idLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, ID_LABEL_WIDTH), y + ID_INPUT_Y, ID_LABEL_WIDTH,
                          L"Табельный номер");
    idEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + ID_INPUT_Y, ID_INPUT_WIDTH);
    EditSetFilter(idEdit, PositiveNumberFilter);
    EditSetEnterAction(idEdit, OnIdEnter);
    LayoutAddComponent(dialog, idLabel);
    LayoutAddComponent(dialog, idEdit);

    surnameLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, SURNAME_LABEL_WIDTH), y + SURNAME_INPUT_Y,
                               SURNAME_LABEL_WIDTH, L"Фамилия");
    surnameEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + SURNAME_INPUT_Y, SURNAME_INPUT_WIDTH);
    LayoutAddComponent(dialog, surnameLabel);
    LayoutAddComponent(dialog, surnameEdit);

    nameLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, NAME_LABEL_WIDTH), y + NAME_INPUT_Y, NAME_LABEL_WIDTH,
                            L"Имя");
    nameEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + NAME_INPUT_Y, NAME_INPUT_WIDTH);
    LayoutAddComponent(dialog, nameLabel);
    LayoutAddComponent(dialog, nameEdit);

    patronymicLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, PATRONYMIC_LABEL_WIDTH), y + PATRONYMIC_INPUT_Y,
                                  PATRONYMIC_LABEL_WIDTH, L"Отчество");
    patronymicEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + PATRONYMIC_INPUT_Y, PATRONYMIC_INPUT_WIDTH);
    LayoutAddComponent(dialog, patronymicLabel);
    LayoutAddComponent(dialog, patronymicEdit);

    yobLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, YOB_LABEL_WIDTH), y + YOB_INPUT_Y, YOB_LABEL_WIDTH,
                           L"Год рождения");
    yobEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + YOB_INPUT_Y, YOB_INPUT_WIDTH);
    EditSetFilter(yobEdit, PositiveNumberFilter);
    LayoutAddComponent(dialog, yobLabel);
    LayoutAddComponent(dialog, yobEdit);

    genderLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, GENDER_LABEL_WIDTH), y + GENDER_INPUT_Y,
                              GENDER_LABEL_WIDTH, L"Пол");
    genderSelect = CreateSelect(dataDialogSelectStyle, x + INPUT_X, y + GENDER_INPUT_Y, GENDER_INPUT_WIDTH, 2, L"М",
                                L"Ж");
    LayoutAddComponent(dialog, genderLabel);
    LayoutAddComponent(dialog, genderSelect);

    profLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, PROF_LABEL_WIDTH), y + PROF_INPUT_Y, PROF_LABEL_WIDTH,
                            L"Профессия");
    profEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + PROF_INPUT_Y, PROF_INPUT_WIDTH);
    LayoutAddComponent(dialog, profLabel);
    LayoutAddComponent(dialog, profEdit);

    expLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, EXP_LABEL_WIDTH), y + EXP_INPUT_Y, EXP_LABEL_WIDTH,
                           L"Опыт работы");
    expEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + EXP_INPUT_Y, EXP_INPUT_WIDTH);
    EditSetFilter(expEdit, PositiveNumberFilter);
    LayoutAddComponent(dialog, expLabel);
    LayoutAddComponent(dialog, expEdit);

    classLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, CLASS_LABEL_WIDTH), y + CLASS_INPUT_Y,
                             CLASS_LABEL_WIDTH, L"Разряд");
    classSelect = CreateSelect(dataDialogSelectStyle, x + INPUT_X, y + CLASS_INPUT_Y, CLASS_INPUT_WIDTH, 3, L"1", L"2",
                               L"3");
    LayoutAddComponent(dialog, classLabel);
    LayoutAddComponent(dialog, classSelect);

    deptLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, DEPT_LABEL_WIDTH), y + DEPT_INPUT_Y, DEPT_LABEL_WIDTH,
                            L"Цех");
    deptEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + DEPT_INPUT_Y, DEPT_INPUT_WIDTH);
    EditSetFilter(deptEdit, PositiveNumberFilter);
    LayoutAddComponent(dialog, deptLabel);
    LayoutAddComponent(dialog, deptEdit);

    plotLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, PLOT_LABEL_WIDTH), y + PLOT_INPUT_Y, PLOT_LABEL_WIDTH,
                            L"Участок");
    plotEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + PLOT_INPUT_Y, PLOT_INPUT_WIDTH);
    EditSetFilter(plotEdit, PositiveNumberFilter);
    LayoutAddComponent(dialog, plotLabel);
    LayoutAddComponent(dialog, plotEdit);

    salaryLabel = CreateLabel(dataDialogLabelStyle, labeloffset(x, SALARY_LABEL_WIDTH), y + SALARY_INPUT_Y,
                              SALARY_LABEL_WIDTH, L"Зарплата");
    salaryEdit = CreateEdit(dataDialogEditStyle, x + INPUT_X, y + SALARY_INPUT_Y, SALARY_INPUT_WIDTH);
    EditSetFilter(salaryEdit, PositiveNumberFilter);
    LayoutAddComponent(dialog, salaryLabel);
    LayoutAddComponent(dialog, salaryEdit);

    confirmButton = CreateButton(dataDialogButtonStyle, x + 5, y + (DIALOG_HEIGHT - 2), 8, L"   Ок   ", OnConfirm);
    cancelButton = CreateButton(dataDialogButtonStyle, x + 23, y + (DIALOG_HEIGHT - 2), 8, L" Отмена ", OnCancel);
    LayoutAddComponent(dialog, confirmButton);
    LayoutAddComponent(dialog, cancelButton);

    errorText = CreateTextArea(dataDialogErrorTextStyle, x + (DIALOG_WIDTH - 30) / 2, y + 1, 30, 2);
    TextAreaSetContent(errorText, L"Некорректный табельный номер или он уже занят");
    LayoutAddComponent(dialog, errorText);
}

void ShowEmptyDialog(int recommendedId, void (*onIdChange)(int id), void (* onConfirm)(void), void (* onCancel)(void)) {
    wchar_t id[ID_INPUT_WIDTH];
    swprintf(id, ID_INPUT_WIDTH, L"%d", recommendedId);
    EditSetValue(idEdit, id);
    EditSetValue(surnameEdit, L"");
    EditSetValue(nameEdit, L"");
    EditSetValue(patronymicEdit, L"");
    EditSetValue(yobEdit, L"");
    SelectSetValue(genderSelect, 0);
    EditSetValue(profEdit, L"");
    EditSetValue(expEdit, L"");
    SelectSetValue(classSelect, 0);
    EditSetValue(deptEdit, L"");
    EditSetValue(plotEdit, L"");
    EditSetValue(salaryEdit, L"");
    idChangeAction = onIdChange;
    confirmAction = onConfirm;
    cancelAction = onCancel;
    ComponentSetVisibility(errorText, false);
    ActivateLayout(dialog);
}

void ShowDataDialog(Employee* e, void (*onIdChange)(int id), void (* onConfirm)(void), void (* onCancel)(void)) {
    if (e == NULL) return;
    wchar_t id[ID_INPUT_WIDTH];
    swprintf(id, ID_INPUT_WIDTH, L"%d", e->id);
    EditSetValue(idEdit, id);
    EditSetValue(surnameEdit, e->surname);
    EditSetValue(nameEdit, e->name);
    EditSetValue(patronymicEdit, e->patronymic);
    wchar_t yob[YOB_INPUT_WIDTH];
    swprintf(yob, YOB_INPUT_WIDTH, L"%d", e->yob);
    EditSetValue(yobEdit, yob);
    SelectSetValue(genderSelect, e->gender ? 0 : 1);
    EditSetValue(profEdit, e->profession);
    wchar_t exp[EXP_INPUT_WIDTH];
    swprintf(exp, EXP_INPUT_WIDTH, L"%d", e->experience);
    EditSetValue(expEdit, exp);
    SelectSetValue(classSelect, 0);
    wchar_t dept[DEPT_INPUT_WIDTH];
    swprintf(dept, DEPT_INPUT_WIDTH, L"%d", e->department);
    EditSetValue(deptEdit, dept);
    wchar_t plot[PLOT_INPUT_WIDTH];
    swprintf(plot, PLOT_INPUT_WIDTH, L"%d", e->plot);
    EditSetValue(plotEdit, plot);
    wchar_t salary[SALARY_INPUT_WIDTH];
    swprintf(salary, SALARY_INPUT_WIDTH, L"%d", e->salary);
    EditSetValue(salaryEdit, salary);
    idChangeAction = onIdChange;
    confirmAction = onConfirm;
    cancelAction = onCancel;
    ComponentSetVisibility(errorText, false);
    ActivateLayout(dialog);
}

int GetEmployeeId(void) {
    return parseInt(EditGetValue(idEdit));
}

wchar_t* GetEmployeeSurname(void) {
    return EditGetValue(surnameEdit);
}

wchar_t* GetEmployeeName(void) {
    return EditGetValue(nameEdit);
}

wchar_t* GetEmployeePatronymic(void) {
    return EditGetValue(patronymicEdit);
}

int GetEmployeeYOB(void) {
    return parseInt(EditGetValue(yobEdit));
}

bool GetEmployeeGender(void) {
    return ValueOfGender(SelectGetValue(genderSelect));
}

wchar_t* GetEmployeeProfession(void) {
    return EditGetValue(profEdit);
}

int GetEmployeeExperience(void) {
    return parseInt(EditGetValue(expEdit));
}

ProfClass GetEmployeeClass(void) {
    return ValueOfProfClass(SelectGetValue(classSelect));
}

int GetEmployeeDepartment(void) {
    return parseInt(EditGetValue(deptEdit));
}

int GetEmployeePlot(void) {
    return parseInt(EditGetValue(plotEdit));
}

int GetEmployeeSalary(void) {
    return parseInt(EditGetValue(salaryEdit));
}

Employee* GetEnteredData(void) {
    Employee* e = malloc(sizeof(Employee));
    int id = parseInt(EditGetValue(idEdit));
    e->id = id;

    EmployeeSetSurname(e, EditGetValue(surnameEdit));

    EmployeeSetName(e, EditGetValue(nameEdit));

    EmployeeSetPatronymic(e, EditGetValue(patronymicEdit));

    int yob = parseInt(EditGetValue(yobEdit));
    e->yob = (short) yob;

    e->gender = ValueOfGender(SelectGetValue(genderSelect));

    EmployeeSetProfession(e, EditGetValue(profEdit));

    int exp = parseInt(EditGetValue(expEdit));
    e->experience = (char) exp;

    e->class = ValueOfProfClass(SelectGetValue(classSelect));

    int dept = parseInt(EditGetValue(deptEdit));
    e->department = (char) dept;

    int plot = parseInt(EditGetValue(plotEdit));
    e->plot = (char) plot;

    int salary = parseInt(EditGetValue(salaryEdit));
    e->salary = salary;

    return e;
}

void DataIdCorrectness(bool correct) {
    if (correct) {
        ButtonSetEnabled(confirmButton, true);
        ComponentSetVisibility(errorText, false);
    } else {
        ButtonSetEnabled(confirmButton, false);
        ComponentSetVisibility(errorText, true);
    }
}

