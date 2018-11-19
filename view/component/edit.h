#ifndef MANUFACTURY_EDIT_H
#define MANUFACTURY_EDIT_H

#include <view/component.h>
#include <view/interactive_panel.h>
#include <global.h>

typedef struct Edit Edit;
typedef struct EditStyle EditStyle;

struct Edit {
    EditStyle* style;
    int size;
    int pos;
    int length;
    wchar_t* data;
    InteractivePanel* panelEditField;
};

struct EditStyle {
    int defaultColor;
    int activeColor;
};

Component* CreateEdit(EditStyle* style, int x, int y, int size);

EditStyle* CreateEditStyle(int defaultColor, int activeColor);

#endif //MANUFACTURY_EDIT_H
