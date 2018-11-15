#ifndef MANUFACTURY_LABEL_H
#define MANUFACTURY_LABEL_H

#include <view/interactive_panel.h>
#include <curses.h>
#include <malloc.h>

typedef struct Label Label;

struct Label {
    int size;
    wchar_t* text;
    InteractivePanel* panelLabel;
};

Component* CreateLabel(int x, int y, int size, wchar_t* text);

#endif //MANUFACTURY_LABEL_H
