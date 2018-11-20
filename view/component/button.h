#ifndef MANUFACTURY_BUTTON_H
#define MANUFACTURY_BUTTON_H

#include <view/interactive_panel.h>

typedef struct Button Button;
typedef struct ButtonStyle ButtonStyle;

struct Button {
    ButtonStyle* style;
    bool enabled;
    int size;
    wchar_t* text;
    InteractivePanel* panel;
    void (* action)(void);
};

struct ButtonStyle {
    int defaultColor;
    int disabledColor;
    int focusedColor;
};

Component* CreateButton(ButtonStyle* style, int x, int y, int size, wchar_t* text, void (* action)(void));

void ButtonSetText(Component* handle, wchar_t* text);

void ButtonSetEnabled(Component* handle, bool enabled);

ButtonStyle* CreateButtonStyle(int defaultColor, int disabledColor, int focusedColor);

#endif //MANUFACTURY_BUTTON_H
