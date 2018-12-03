#include <view/component/textarea.h>
#include <src/log.h>
#include "dialog.h"
#include "styles.h"

#define DIALOG_WIDTH 23
#define DIALOG_HEIGHT 10
#define YES_BTN_X 1
#define NO_BTN_X YES_BTN_X+1+6
#define CANCEL_BTN_X NO_BTN_X+1+5

Layout* confirmationDialog;
Component* confirmationText;
Component* yesButton;
Component* noButton;
Component* cancelButton;
void (* yesAction)(void) = NULL;
void (* noAction)(void) = NULL;
void (* cancelAction)(void) = NULL;

Layout* messageDialog;
Component* messageText;
Component* okButton;
void (* okAction)(void) = NULL;

void OnYesClick(Component* handle) {
    ActivateLayout(NULL);
    if (yesAction != NULL) yesAction();
}

void OnNoClick(Component* handle) {
    ActivateLayout(NULL);
    if (noAction != NULL) noAction();
}

void OnCancelClick(Component* handle) {
    ActivateLayout(NULL);
    if (cancelAction != NULL) cancelAction();
}

void OnOkClick(Component* handle) {
    ActivateLayout(NULL);
    if (okAction != NULL) okAction();
}

void InitDialogsLayouts(int color) {
    int x = (COLS - DIALOG_WIDTH) / 2;
    int y = (LINES - DIALOG_HEIGHT) / 2;
    int btnY = y + DIALOG_HEIGHT - 2;

    confirmationDialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(confirmationDialog->window, COLOR_PAIR(color));
    confirmationText = CreateTextArea(textAreaStyle, x + 1, y + 1, DIALOG_WIDTH - 2, DIALOG_HEIGHT - 4);
    yesButton = CreateButton(yesButtonStyle, x + YES_BTN_X, btnY, 6, L"  Да  ", OnYesClick);
    noButton = CreateButton(noButtonStyle, x + NO_BTN_X, btnY, 5, L" Нет ", OnNoClick);
    cancelButton = CreateButton(cancelButtonStyle, x + CANCEL_BTN_X, btnY, 8, L" Отмена ", OnCancelClick);
    LayoutAddComponent(confirmationDialog, confirmationText);
    LayoutAddComponent(confirmationDialog, yesButton);
    LayoutAddComponent(confirmationDialog, noButton);
    LayoutAddComponent(confirmationDialog, cancelButton);

    messageDialog = CreateLayout(x, y, DIALOG_WIDTH, DIALOG_HEIGHT);
    wbkgd(messageDialog->window, COLOR_PAIR(color));
    messageText = CreateTextArea(textAreaStyle, x + 1, y + 1, DIALOG_WIDTH - 2, DIALOG_HEIGHT - 2);
    okButton = CreateButton(cancelButtonStyle, x + (DIALOG_WIDTH - 4) / 2, btnY, 4, L" Ок ", OnOkClick);
    LayoutAddComponent(messageDialog, messageText);
    LayoutAddComponent(messageDialog, okButton);
}

void ShowConfirmationDialog(wchar_t* message, void (* onYes)(void), void (* onNo)(void), void (* onCancel)(void)) {
    TextAreaSetContent(confirmationText, message);
    yesAction = onYes;
    noAction = onNo;
    cancelAction = onCancel;
    ActivateLayout(confirmationDialog);
}

void ShowMessageDialog(wchar_t* message, void (* onOk)(void)) {
    okAction = onOk;
    ActivateLayout(messageDialog);
    TextAreaSetContent(messageText, message);
}

