#ifndef MANUFACTURY_SELECT_H
#define MANUFACTURY_SELECT_H

#include <tui/interactive_panel.h>

typedef struct Select Select;
typedef struct SelectStyle SelectStyle;

struct Select {
    SelectStyle* style;
    bool enabled;
    bool active;
    int width;
    int selected;
    int count;
    wchar_t** options;
    InteractivePanel* selectedPanel;
    InteractivePanel* listPanel;
    void (* action)(Component* handle);
};

struct SelectStyle {
    int defaultColor;
    int disabledColor;
    int focusedColor;
    int listColor;
    int activeItemColor;
};

Component* CreateSelect(SelectStyle* style, int x, int y, int width, int count, ...);

void SelectSetEnabled(Component* handle, bool enabled);

void SelectSetValue(Component* handle, int value);

int SelectGetValue(Component* handle);

SelectStyle* CreateSelectStyle(int defaultColor, int disabledColor, int focusedColor, int listColor, int activeItemColor);

#endif //MANUFACTURY_SELECT_H
