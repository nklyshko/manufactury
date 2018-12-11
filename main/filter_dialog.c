#include <tui/styles.h>
#include "filter_dialog.h"

#define DIALOG_WIDTH 36
#define DIALOG_HEIGHT 17

Layout* filterDialog;
Component* fieldSelect;
Component* valueEdit;
void (* confirmAction)(int fieldId, wchar_t* value);

void OnFilterConfirm(Component* handle) {
    ActivateLayout(NULL);
    confirmAction(SelectGetValue(fieldSelect), EditGetValue(valueEdit));
}

void OnFilterCancel(Component* handle) {
    ActivateLayout(NULL);
}

void InitFilterDialog(int color) {
    int x = (COLS - DIALOG_WIDTH) / 2;
    int y = (LINES - DIALOG_HEIGHT) / 2;
    filterDialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(filterDialog->window, COLOR_PAIR(color));

    Component* dialogLabel = CreateLabel(dataDialogLabelStyle, x + (DIALOG_WIDTH - 13) / 2, y + 1, 16, L"Поиск записей");
    LayoutAddComponent(filterDialog, dialogLabel);
    fieldSelect = CreateSelect(dataDialogSelectStyle, x + 1, y + 3, 16, 12,
            L"Табельный номер", L"Фамилия", L"Имя", L"Отчество", L"Год рождения", L"Пол", L"Профессия", L"Опыт работы",
            L"Разряд", L"Цех", L"Участок", L"Зарплата");
    LayoutAddComponent(filterDialog, fieldSelect);
    valueEdit = CreateEdit(dataDialogEditStyle, x + 18, y + 3, 16);
    LayoutAddComponent(filterDialog, valueEdit);
    Component* okButton = CreateButton(dataDialogButtonStyle, x + 6, y + DIALOG_HEIGHT - 2, 6, L"  Ок  ", OnFilterConfirm);
    LayoutAddComponent(filterDialog, okButton);
    Component* cancelButton = CreateButton(dataDialogButtonStyle, x + 20, y + DIALOG_HEIGHT - 2, 6, L"Отмена", OnFilterCancel);
    LayoutAddComponent(filterDialog, cancelButton);
}

void ShowFilterDialog(void (* onConfirm)(int fieldId, wchar_t* value)) {
    EditSetValue(valueEdit, L"");
    confirmAction = onConfirm;
    ActivateLayout(filterDialog);
}

