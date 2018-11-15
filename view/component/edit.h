#ifndef MANUFACTURY_EDIT_H
#define MANUFACTURY_EDIT_H

#include <view/component.h>
#include <view/interactive_panel.h>
#include <global.h>

typedef struct Edit Edit;

struct Edit {
    int size;
    int pos;
    int length;
    wchar_t* data;
    InteractivePanel* panelEditField;
};

Component* CreateEdit(int x, int y, int size);

#endif //MANUFACTURY_EDIT_H
