#include <src/log.h>
#include "label.h"


void LabelShow(Component* handle) {
    Label* label = handle->spec;
    wbkgd(label->panelLabel->window, COLOR_PAIR(label->style->color));
    PanelShow(label->panelLabel);
}

void LabelHide(Component* handle) {
    Label* label = handle->spec;
    PanelHide(label->panelLabel);
}

bool LabelOnFocusGet(Component* handle) {
    return false;
}

Component* CreateLabel(LabelStyle* style, int x, int y, int size, wchar_t* text) {
    Component* handle = CreateComponent();
    Label* label = malloc(sizeof(Label));
    label->style = style;
    label->size = size;
    label->text = malloc(sizeof(wchar_t) * (size + 1));
    wmemcpy_s(label->text, (size_t) size, text, (size_t) size); //wcscpy_s не работает

    InteractivePanel* panelLabel = CreateInteractivePanel(handle, x, y, size, 1);
    label->panelLabel = panelLabel;
    wmove(panelLabel->window, 0, 0);
    waddwstr(panelLabel->window, label->text);

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Label", GetNextId());

    handle->spec = label;
    handle->Show = LabelShow;
    handle->Hide = LabelHide;
    handle->OnFocusGet = LabelOnFocusGet;
    return handle;
}

void LabelSetText(Component* handle, wchar_t* text) {
    Label* label = handle->spec;
    wmemcpy_s(label->text, (size_t) label->size, text, (size_t) label->size);
    wmove(label->panelLabel->window, 0, 0);
    waddwstr(label->panelLabel->window, label->text);
}

LabelStyle* CreateLabelStyle(int color) {
    LabelStyle* style = malloc(sizeof(LabelStyle));
    style->color = color;
    return style;
}