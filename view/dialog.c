#include <view/component/textarea.h>
#include "dialog.h"
#include "styles.h"

#define DIALOG_WIDTH 23
#define DIALOG_HEIGHT 10
#define YES_BTN_X 1
#define NO_BTN_X YES_BTN_X+1+6
#define CANCEL_BTN_X NO_BTN_X+1+5

Layout* dialog;
Component* text;
Component* yesButton;
Component* noButton;
Component* cancelButton;
void (* yesAction)(void);
void (* noAction)(void);
void (* cancelAction)(void);

void OnYesClick(Component* handle) {
    ActivateLayout(NULL);
    yesAction();
}

void OnNoClick(Component* handle) {
    ActivateLayout(NULL);
    noAction();
}

void OnCancelClick(Component* handle) {
    ActivateLayout(NULL);
    cancelAction();
}

void InitDialogLayout(int color) {
    int x = (COLS - DIALOG_WIDTH) / 2;
    int y = (LINES - DIALOG_HEIGHT) / 2;
    dialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(dialog->window, COLOR_PAIR(color));
    text = CreateTextArea(textAreaStyle, x + 1, y + 1, DIALOG_WIDTH - 2, DIALOG_HEIGHT - 4);
    int btnY = y + DIALOG_HEIGHT - 2;
    yesButton = CreateButton(yesButtonStyle, x + YES_BTN_X, btnY, 6, L"  Да  ", OnYesClick);
    noButton = CreateButton(noButtonStyle, x + NO_BTN_X, btnY, 5, L" Нет ", OnNoClick);
    cancelButton = CreateButton(cancelButtonStyle, x + CANCEL_BTN_X, btnY, 8, L" Отмена ", OnCancelClick);
    LayoutAddComponent(dialog, text);
    LayoutAddComponent(dialog, yesButton);
    LayoutAddComponent(dialog, noButton);
    LayoutAddComponent(dialog, cancelButton);
}

void ShowDialog(wchar_t* message, void (* onYes)(void), void (* onNo)(void), void (* onCancel)(void)) {
    TextAreaSetContent(text, message);
    yesAction = onYes;
    noAction = onNo;
    cancelAction = onCancel;
    ActivateLayout(dialog);
}