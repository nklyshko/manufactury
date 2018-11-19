#include "button.h"


void ButtonOnMouseClick(InteractivePanel* handle, MEVENT event) {
    Button* button = handle->holder->spec;
    FocusComponent(NULL);
    button->action();
}

void ButtonShow(Component* handle) {
    Button* button = handle->spec;
    if (button->enabled) {
        wbkgd(button->panelButton->window, COLOR_PAIR(button->style->defaultColor));
    } else {
        wbkgd(button->panelButton->window, COLOR_PAIR(button->style->disabledColor));
    }
    PanelShow(button->panelButton);
}

void ButtonHide(Component* handle) {
    Button* button = handle->spec;
    PanelHide(button->panelButton);
}

void ButtonOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    Button* button = handle->spec;
    if (key == KEY_ENTER) {
        FocusComponent(NULL);
        button->action();
    }
}

bool ButtonOnFocusGet(Component* handle) {
    Button* button = handle->spec;
    if (button->enabled) {
        wbkgd(button->panelButton->window, COLOR_PAIR(button->style->focusedColor));
        return true;
    } else {
        return false;
    }
}

void ButtonOnFocusLost(Component* handle) {
    Button* button = handle->spec;
    if (button->enabled) {
        wbkgd(button->panelButton->window, COLOR_PAIR(button->style->defaultColor));
    } else {
        wbkgd(button->panelButton->window, COLOR_PAIR(button->style->disabledColor));
    }
}

Component* CreateButton(ButtonStyle* style, int x, int y, int size, wchar_t* text, void (* action)(void)) {
    Component* handle = CreateComponent();
    InteractivePanel* panelButton = CreateInteractivePanel(handle, x, y, size, 1);
    Button* button = malloc(sizeof(Button));
    button->style = style;
    button->enabled = true;
    button->size = size;
    button->action = action;
    button->text = malloc(sizeof(wchar_t) * (size + 1));
    wmemcpy_s(button->text, (size_t) size, text, (size_t) size); //wcscpy_s не работает
    button->panelButton = panelButton;
    wbkgd(panelButton->window, COLOR_PAIR(button->style->defaultColor));
    wmove(panelButton->window, 0, 0);
    waddwstr(panelButton->window, button->text);
    panelButton->OnMouseClick = ButtonOnMouseClick;

    handle->spec = button;

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Button", GetNextId());

    handle->Show = ButtonShow;
    handle->Hide = ButtonHide;
    handle->OnKeyClick = ButtonOnKeyClick;
    handle->OnFocusGet = ButtonOnFocusGet;
    handle->OnFocusLost = ButtonOnFocusLost;
    return handle;
}

void ButtonSetText(Component* handle, wchar_t* text) {
    Button* button = handle->spec;
    wmemcpy_s(button->text, (size_t) button->size, text, (size_t) button->size);
    wmove(button->panelButton->window, 0, 0);
    waddwstr(button->panelButton->window, button->text);
}

void ButtonSetEnabled(Component* handle, bool enabled) {
    Button* button = handle->spec;
    button->enabled = enabled;
    WINDOW* w = button->panelButton->window;
    if (enabled) {
        wbkgd(w, COLOR_PAIR(button->style->defaultColor));
    } else {
        wbkgd(w, COLOR_PAIR(button->style->disabledColor));
    }
}

ButtonStyle* CreateButtonStyle(int defaultColor, int disabledColor, int focusedColor) {
    ButtonStyle* style = malloc(sizeof(ButtonStyle));
    style->defaultColor = defaultColor;
    style->disabledColor = disabledColor;
    style->focusedColor = focusedColor;
    return style;
}