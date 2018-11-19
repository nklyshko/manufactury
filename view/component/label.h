#ifndef MANUFACTURY_LABEL_H
#define MANUFACTURY_LABEL_H

#include <view/interactive_panel.h>
#include <curses.h>
#include <malloc.h>

typedef struct Label Label;
typedef struct LabelStyle LabelStyle;

struct Label {
    LabelStyle* style;
    int size;
    wchar_t* text;
    InteractivePanel* panelLabel;
};

struct LabelStyle {
    int color;
};

Component* CreateLabel(LabelStyle* style, int x, int y, int size, wchar_t* text);

void LabelSetText(Component* handle, wchar_t* text);

LabelStyle* CreateLabelStyle(int color);

#endif //MANUFACTURY_LABEL_H
