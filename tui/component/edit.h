#ifndef MANUFACTURY_EDIT_H
#define MANUFACTURY_EDIT_H

#include <tui/interactive_panel.h>

typedef struct Edit Edit;
typedef struct EditStyle EditStyle;

struct Edit {
    EditStyle* style;
    bool enabled;
    int size;
    int pos;
    int selected;
    int length;
    wchar_t* value;
    bool (* filter)(int s);
    InteractivePanel* panel;
    void (* OnEnter)(Component* handle);
};

struct EditStyle {
    int defaultColor;
    int disabledColor;
    int activeColor;
};

Component* CreateEdit(EditStyle* style, int x, int y, int size);

void EditSetEnabled(Component* handle, bool enabled);

void EditSetValue(Component* handle, wchar_t* value);

void EditSetFilter(Component* handle, bool (* filter)(int s));

void EditSetEnterAction(Component* handle, void (* OnEnter)(Component* handle));

wchar_t* EditGetValue(Component* handle);

EditStyle* CreateEditStyle(int defaultColor, int disabledColor, int activeColor);

#endif //MANUFACTURY_EDIT_H
