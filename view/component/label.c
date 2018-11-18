#include <src/log.h>
#include "label.h"

void LabelShow(Component* handle) {
    Label* label = handle->spec;
    //TODO: инкапсулировать вызов в InteractivePanel
    show_panel(label->panelLabel->panel);
}

void LabelHide(Component* handle) {
    Label* label = handle->spec;
    //TODO: инкапсулировать вызов в InteractivePanel
    hide_panel(label->panelLabel->panel);
}

bool LabelOnFocusGet(Component* component) {
    return false;
}

Component* CreateLabel(int x, int y, int size, wchar_t* text) {
    Component* handle = CreateComponent();
    InteractivePanel* panelLabel = CreateInteractivePanel(handle, x, y, size, 1);
    Label* label = malloc(sizeof(Label));
    label->size = size;
    label->text = malloc(sizeof(wchar_t) * (size + 1));
    wmemcpy_s(label->text, (rsize_t) size, text, (size_t) size); //wcscpy_s не работает
    label->panelLabel = panelLabel;
    wmove(panelLabel->window, 0, 0);
    waddwstr(panelLabel->window, label->text);

    handle->spec = label;

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Label", GetNextId());

    handle->Show = LabelShow;
    handle->Hide = LabelHide;
    handle->OnFocusGet = LabelOnFocusGet;
    return handle;
}
