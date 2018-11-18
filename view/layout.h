#ifndef MANUFACTURY_LAYOUT_H
#define MANUFACTURY_LAYOUT_H

#include <list.h>
#include "component.h"

typedef struct Layout Layout;

struct Layout {
    PANEL* layoutPanel;
    Component* firstComponent;
    Component* lastComponent;
};

Layout* CreateLayout(int x, int y, int width, int height);

void LayoutAddComponent(Layout* layout, Component* component);

void ShowLayout(Layout* layout);

void HideLayout(Layout* layout);

void ActivateLayout(Layout* layout);

void SetMainLayout(Layout* layout);

void LayoutHandleMouseEvent(MEVENT event);

void LayoutHandleKeyboardEvent(int key, unsigned long modifiers);

#endif //MANUFACTURY_LAYOUT_H
