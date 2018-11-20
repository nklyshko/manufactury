#ifndef MANUFACTURY_EDIT_H
#define MANUFACTURY_EDIT_H

#include <view/component.h>
#include <view/interactive_panel.h>

typedef struct Edit Edit;
typedef struct EditStyle EditStyle;

struct Edit {
    EditStyle* style;
    bool enabled;
    int size;
    int pos;
    int selected;
    int length;
    wchar_t* data;
    void (* action)(Component* handle);
    InteractivePanel* panel;
};

struct EditStyle {
    int defaultColor;
    int disabledColor;
    int activeColor;
};

Component* CreateEdit(EditStyle* style, int x, int y, int size);

void EditSetEnabled(Component* handle, bool enabled);

void EditSetEnterAction(Component* handle, void (* action)(Component* handle));

EditStyle* CreateEditStyle(int defaultColor, int disabledColor, int activeColor);

#endif //MANUFACTURY_EDIT_H
