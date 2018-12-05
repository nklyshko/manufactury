#ifndef MANUFACTURY_BUTTON_H
#define MANUFACTURY_BUTTON_H

#include <tui/interactive_panel.h>

typedef struct Button Button;
typedef struct ButtonStyle ButtonStyle;

struct Button {
    ButtonStyle* style;
    bool enabled;
    int size;
    wchar_t* text;
    InteractivePanel* panel;
    void (* OnButtonClick)(Component* handle);
};

struct ButtonStyle {
    int defaultColor;
    int disabledColor;
    int focusedColor;
};

Component* CreateButton(ButtonStyle* style, int x, int y, int size, wchar_t* text, void (* OnButtonClick)(Component* handle));

void ButtonSetText(Component* handle, wchar_t* text);

void ButtonSetEnabled(Component* handle, bool enabled);

ButtonStyle* CreateButtonStyle(int defaultColor, int disabledColor, int focusedColor);

#endif //MANUFACTURY_BUTTON_H
