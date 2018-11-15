#ifndef MANUFACTURY_INTERACTIVE_PANEL_H
#define MANUFACTURY_INTERACTIVE_PANEL_H

#include <panel.h>
#include "component.h"

typedef struct InteractivePanel InteractivePanel;

struct InteractivePanel {
    PANEL* panel;
    WINDOW* window;
    Component* holder;
    void (* OnMouseClick)(InteractivePanel* handle, MEVENT event);
};

InteractivePanel* CreateInteractivePanel(Component* holder, int x, int y, int width, int height);

#endif //MANUFACTURY_INTERACTIVE_PANEL_H
