#ifndef MANUFACTURY_SCROLL_BAR_H
#define MANUFACTURY_SCROLL_BAR_H

#include <tui/layout.h>
#include <tui/interactive_panel.h>

typedef struct ScrollBar ScrollBar;
typedef struct ScrollBarStyle ScrollBarStyle;

struct ScrollBar {
    ScrollBarStyle* style;
    Layout* layout;
    int height;
    int thumb;
    int pos;
    int size;
    int count;
    int number;
    int step;
    InteractivePanel* panel;
};

struct ScrollBarStyle {
    int color;
};

Component* CreateScrollBar(ScrollBarStyle* style, int x, int y, int height, Layout* layout);

void ScrollBarSetNumber(Component* handle, int number);

void ScrollBarSetCount(Component* handle, int count);

ScrollBarStyle* CreateScrollBarStyle(int color);


#endif //MANUFACTURY_SCROLL_BAR_H
