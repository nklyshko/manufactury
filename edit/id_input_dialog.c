#include <tui/layout.h>
#include <tui/styles.h>
#include "id_input_dialog.h"

#define DIALOG_WIDTH 33
#define DIALOG_HEIGHT 5

void (* confirmAction)(int id);

Layout* idInputDialog;
Component* idInput;

void OnIdConfirm(Component* handle) {
    ActivateLayout(NULL);
    int id = parseInt(EditGetValue(idInput));
    confirmAction(id);
}

void OnIdCancel(Component* handle) {
    ActivateLayout(NULL);
}

void InitIdInputDialog(int color) {
    int x = (COLS - DIALOG_WIDTH) / 2;
    int y = (LINES - DIALOG_HEIGHT) / 2;
    idInputDialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(idInputDialog->window, COLOR_PAIR(color));

    Component* label = CreateLabel(labelStyle, x + 1, y + 1, 23, L"Введите табельный номер");
    LayoutAddComponent(idInputDialog, label);
    idInput = CreateEdit(dataDialogEditStyle, x + 25, y + 1, 5);
    LayoutAddComponent(idInputDialog, idInput);
    Component* okButton = CreateButton(cancelButtonStyle, x + 6, y + DIALOG_HEIGHT - 2, 6, L"  Ок  ", OnIdConfirm);
    LayoutAddComponent(idInputDialog, okButton);
    Component* cancelButton = CreateButton(cancelButtonStyle, x + 20, y + DIALOG_HEIGHT - 2, 6, L"Отмена", OnIdCancel);
    LayoutAddComponent(idInputDialog, cancelButton);
}

void ShowIdInputDialog(void (* onConfirm)(int)) {
    EditSetValue(idInput, L"");
    confirmAction = onConfirm;
    ActivateLayout(idInputDialog);
}
