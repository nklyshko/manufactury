#include "report_param_dialog.h"

#define DIALOG_WIDTH 33
#define DIALOG_HEIGHT 7

Layout* reportParamDialog;
Component* paramEdit;
Component* okButton;
void (* confirmAction)(wchar_t* param);

void OnParamConfirm(Component* handle) {
    confirmAction(EditGetValue(paramEdit));
}

void OnParamCancel(Component* handle) {
    ActivateLayout(NULL);
}

void OnParamChange(Component* handle) {
    if (wcslen(EditGetValue(paramEdit)) > 0) {
        ButtonSetEnabled(okButton, true);
    } else {
        ButtonSetEnabled(okButton, false);
    }
}


void InitReportParamDialog(int color) {
    int x = (COLS - DIALOG_WIDTH) / 2;
    int y = (LINES - DIALOG_HEIGHT) / 2;
    reportParamDialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(reportParamDialog->window, COLOR_PAIR(color));

    Component* dialogLabel = CreateLabel(dataDialogLabelStyle, x + (DIALOG_WIDTH - 16) / 2, y + 1, 16, L"Генерация отчета");
    LayoutAddComponent(reportParamDialog, dialogLabel);
    Component* paramLabel = CreateLabel(dataDialogLabelStyle, x + (DIALOG_WIDTH / 2 - 12), y + 3, 9, L"Профессия");
    LayoutAddComponent(reportParamDialog, paramLabel);
    paramEdit = CreateEdit(dataDialogEditStyle, x + (DIALOG_WIDTH / 2 - 1), y + 3, 16);
    EditSetEnterAction(paramEdit, OnParamChange);
    LayoutAddComponent(reportParamDialog, paramEdit);
    okButton = CreateButton(dataDialogButtonStyle, x + 6, y + DIALOG_HEIGHT - 2, 6, L"  Ок  ", OnParamConfirm);
    LayoutAddComponent(reportParamDialog, okButton);
    Component* cancelButton = CreateButton(dataDialogButtonStyle, x + 20, y + DIALOG_HEIGHT - 2, 6, L"Отмена", OnParamCancel);
    LayoutAddComponent(reportParamDialog, cancelButton);
}

void ShowReportParamDialog(void (* onConfirm)(wchar_t* param)) {
    EditSetValue(paramEdit, L"");
    ButtonSetEnabled(okButton, false);
    confirmAction = onConfirm;
    ActivateLayout(reportParamDialog);
}
