#include <src/log.h>
#include <minmax.h>
#include "layout.h"
#include "interactive_panel.h"


Layout* activeLayout = NULL;
Layout* mainLayout; //Основное окно программы. Если открыты другие, то оно на фоне

void DefaultOnScrollUp(ScrollType type) {
    //noop
}

void DefaultOnScrollDown(ScrollType type) {
    //noop
}

Layout* CreateLayout(int x, int y, int width, int height) {
    Layout* layout = malloc(sizeof(Layout));
    WINDOW* window = newwin(height, width, y, x);
    PANEL* layoutPanel = new_panel(window);
    hide_panel(layoutPanel);
    set_panel_userptr(layoutPanel, NULL);
    layout->panel = layoutPanel;
    layout->window = window;
    layout->OnScrollUp = DefaultOnScrollUp;
    layout->OnScrollDown = DefaultOnScrollDown;
    return layout;
}

void LayoutAddComponent(Layout* layout, Component* component) {
    component->nextFocus = NULL;
    if (layout->lastComponent == NULL) {
        layout->firstComponent = component;
        layout->lastComponent = component;
    } else {
        layout->lastComponent->nextFocus = component;
        layout->lastComponent = component;
    }
}

void ShowLayout(Layout* layout) {
    show_panel(layout->panel);
    Component* component = layout->firstComponent;
    while (component != NULL) {
        ShowComponent(component);
        component = component->nextFocus;
    }
}

void HideLayout(Layout* layout) {
    hide_panel(layout->panel);
    Component* component = layout->firstComponent;
    while (component != NULL) {
        HideComponent(component);
        component = component->nextFocus;
    }
}

void ActivateLayout(Layout* layout) {
    if (activeLayout != NULL && activeLayout != mainLayout) {
        HideLayout(activeLayout);
        activeLayout = mainLayout;
    }
    FocusSingleComponent(NULL);
    if (layout != NULL) {
        ShowLayout(layout);
        activeLayout = layout;
    }
}

void SetMainLayout(Layout* layout) {
    mainLayout = layout;
    ActivateLayout(mainLayout);
}

void LayoutHandleMouseEvent(MEVENT event) {
    if (event.bstate & BUTTON4_PRESSED) {
        activeLayout->OnScrollUp(SINGLE);
    } else if (event.bstate & BUTTON5_PRESSED) {
        activeLayout->OnScrollDown(SINGLE);
    } else {
        int mouseX = event.x;
        int mouseY = event.y;
        WINDOW* w = panel_window(activeLayout->panel);
        int y = getbegy(w);
        int x = getbegx(w);
        int height = getmaxy(w);
        int width = getmaxx(w);
        if (mouseX < x || mouseY < y || mouseX >= x + width || mouseY >= y + height) {
            beep();
            return;
        }
        ComponentHandleMouseEvent(event);
    }
}

void LayoutHandleKeyboardEvent(int key, unsigned long modifiers) {
    if (key == KEY_TAB) {
        Component* component = GetFocusedComponent();
        if (component != NULL && component->OnFocusChange(component)) {
            //Перефокусировка внутри компонента
            return;
        }
        FocusNextComponent(activeLayout->firstComponent);
    } else if (key == KEY_PGUP) {
        activeLayout->OnScrollUp(PAGE);
    } else if (key == KEY_PGDOWN) {
        activeLayout->OnScrollDown(PAGE);
    } else {
        ComponentHandleKeyboardEvent(key, modifiers);
    }
}