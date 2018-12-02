#ifndef MANUFACTURY_TEXTAREA_H
#define MANUFACTURY_TEXTAREA_H

#include <view/interactive_panel.h>

typedef struct TextArea TextArea;
typedef struct TextAreaStyle TextAreaStyle;

struct TextArea {
    TextAreaStyle* style;
    int width;
    int height;
    int size;
    wchar_t* text;
    InteractivePanel* panel;
};

struct TextAreaStyle {
    int color;
};

Component* CreateTextArea(TextAreaStyle* style, int x, int y, int width, int height);

void TextAreaSetContent(Component* handle, wchar_t* text);

TextAreaStyle* CreateTextAreaStyle(int color);

#endif //MANUFACTURY_TEXTAREA_H
