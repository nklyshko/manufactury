#include <global.h>
#include <src/log.h>
#include "component.h"
#include "interactive_panel.h"

void DefaultOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    //noop
};
void DefaultOnFocusGet(Component* handle) {
    //noop
};
bool DefaultOnFocusChange(Component* handle) {
    return false;
};
void DefaultOnFocusLost(Component* handle) {
    //noop
};

Component* focusedComponent = NULL;

Component* CreateComponent() {
    Component* component = malloc(sizeof(Component));
    component->OnKeyClick = DefaultOnKeyClick;
    component->OnFocusGet = DefaultOnFocusGet;
    component->OnFocusChange = DefaultOnFocusChange;
    component->OnFocusLost = DefaultOnFocusLost;
    return component;
}

void HandleMouseEvent(MEVENT event) {
    int mouseX = event.x;
    int mouseY = event.y;
    PANEL* panel = stack_top_panel();
    if (panel == NULL) return;

    while (panel != NULL) {
        WINDOW* w = panel_window(panel);
        int y = getbegy(w);
        int x = getbegx(w);
        int height = getmaxy(w);
        int width = getmaxx(w);
        //log_debug("handleEvent %d <= %d < %d  &&  %d <= %d < %d");
        if (mouseY >= y && mouseX >= x && mouseY < y + height && mouseX < x + width) {
            event.y = mouseY - y;
            event.x = mouseX - x;
            break;
        } else {
            panel = panel_below(panel);
        }
    }
    if (panel == NULL) return;
    log_debug("PANEL not NULL");

    InteractivePanel* interactivePanel = (InteractivePanel*) panel_userptr(panel);
    Component* component = NULL;
    if (interactivePanel != NULL) {
        log_debug("Interactive panel not NULL");
        component = interactivePanel->holder;
    }

    if (component != focusedComponent) {
        if (focusedComponent != NULL) {
            focusedComponent->OnFocusLost(focusedComponent);
        }
        log_debug("New focus: %s", component == NULL ? "null" : component->id);
        focusedComponent = component;
        if (focusedComponent != NULL) {
            focusedComponent->OnFocusGet(focusedComponent);
        }
    }
    if (interactivePanel != NULL) {
        interactivePanel->OnMouseClick(interactivePanel, event);
    }
}

void HandleKeyboardEvent(int key, unsigned long modifiers) {
    if (focusedComponent != NULL) {
        focusedComponent->OnKeyClick(focusedComponent, key, modifiers);
    }
}