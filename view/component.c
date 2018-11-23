#include <global.h>
#include <src/log.h>
#include "component.h"
#include "interactive_panel.h"

#ifdef KEY_TAB
#undef KEY_TAB
#endif
#define KEY_TAB 9

void defaultShow(Component* component) {
    //noop
}
void defaultHide(Component* component) {
    //noop
}
void defaultOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    //noop
};
bool defaultOnFocusGet(Component* handle) {
    return true;
};
bool defaultOnFocusChange(Component* handle) {
    return false;
};
void defaultOnFocusLost(Component* handle) {
    //noop
};

Component* focusedComponent = NULL;

Component* CreateComponent() {
    Component* component = malloc(sizeof(Component));
    component->custom = NULL;
    component->nextFocus = NULL;
    component->Show = defaultShow;
    component->Hide = defaultHide;
    component->OnKeyClick = defaultOnKeyClick;
    component->OnFocusGet = defaultOnFocusGet;
    component->OnFocusChange = defaultOnFocusChange;
    component->OnFocusLost = defaultOnFocusLost;
    return component;
}

void ShowComponent(Component* component) {
    component->Show(component);
}

void HideComponent(Component* component) {
    component->Hide(component);
}

void FocusSingleComponent(Component* component) {
    if (focusedComponent != component) {
        Component* defocus = focusedComponent;
        focusedComponent = component;
        if (defocus != NULL) {
            defocus->OnFocusLost(defocus);
        }
        if (focusedComponent != NULL && !focusedComponent->OnFocusGet(focusedComponent)) {
            focusedComponent = NULL;
        }
    }
}

void FocusNextComponent(Component* resetComponent) {
    if (focusedComponent == NULL) {
        focusedComponent = resetComponent;
    } else {
        Component* component = focusedComponent;
        focusedComponent = component->nextFocus;
        if (focusedComponent == NULL) {
            focusedComponent = resetComponent;
        }
        component->OnFocusLost(component);
    }
    if (focusedComponent != NULL) {
        while (!focusedComponent->OnFocusGet(focusedComponent)) {
            if (focusedComponent->nextFocus == NULL) {
                if (resetComponent != NULL) {
                    focusedComponent = resetComponent;
                    resetComponent = NULL;
                } else {
                    break;
                }
            } else {
                focusedComponent = focusedComponent->nextFocus;
            }
        }
    }
}

void DefocusComponent(Component* component) {
    if (focusedComponent == component) {
        FocusNextComponent(NULL);
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
    FocusSingleComponent(component);
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