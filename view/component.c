#include <global.h>
#include <src/log.h>
#include "component.h"
#include "interactive_panel.h"

#ifdef KEY_TAB
#undef KEY_TAB
#endif
#define KEY_TAB 9

void DefaultShow(Component* component) {
    //noop
}
void DefaultHide(Component* component) {
    //noop
}
void DefaultOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    //noop
};
bool DefaultOnFocusGet(Component* handle) {
    return true;
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
    component->Show = DefaultShow;
    component->Hide = DefaultHide;
    component->OnKeyClick = DefaultOnKeyClick;
    component->OnFocusGet = DefaultOnFocusGet;
    component->OnFocusChange = DefaultOnFocusChange;
    component->OnFocusLost = DefaultOnFocusLost;
    return component;
}

void ShowComponent(Component* component) {
    component->Show(component);
}

void HideComponent(Component* component) {
    component->Hide(component);
}

void FocusComponent(Component* component) {
    if (component != focusedComponent) {
        if (focusedComponent != NULL) {
            focusedComponent->OnFocusLost(focusedComponent);
        }
        log_debug("New focus: %s", component == NULL ? "null" : component->id);
        focusedComponent = component;
        if (focusedComponent != NULL) {
            if (!focusedComponent->OnFocusGet(focusedComponent)) {
                FocusComponent(focusedComponent->nextFocus);
            }
        }
    }
}

Component* GetFocusedComponent(void) {
    return focusedComponent;
}

void ComponentHandleMouseEvent(MEVENT event) {
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
        if (mouseX >= x && mouseY >= y && mouseX < x + width && mouseY < y + height) {
            event.y = mouseY - y;
            event.x = mouseX - x;
            break;
        } else {
            panel = panel_below(panel);
        }
    }
    if (panel == NULL) return;

    InteractivePanel* interactivePanel = (InteractivePanel*) panel_userptr(panel);
    Component* component = NULL;
    if (interactivePanel != NULL) {
        component = interactivePanel->holder;
    }
    FocusComponent(component);
    if (interactivePanel != NULL) {
        interactivePanel->OnMouseClick(interactivePanel, event);
    }
}

void ComponentHandleKeyboardEvent(int key, unsigned long modifiers) {
    if (focusedComponent != NULL) {
        focusedComponent->OnKeyClick(focusedComponent, key, modifiers);
    }
}

int nextId = 1;
//debug???
int GetNextId() {
    return nextId++;
}