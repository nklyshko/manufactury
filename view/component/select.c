#include "select.h"


void defaultSelectEnterAction(Component* handle) {
    //noop
}

void SelectSetSelected(Select* select, int selected) {
    WINDOW* l = select->listPanel->window;
    mvwchgat(l, select->selected, 0, select->width, 0, (short) select->style->listColor, NULL);
    select->selected = selected;
    mvwchgat(l, select->selected, 0, select->width, 0, (short) select->style->activeItemColor, NULL);
    WINDOW* s = select->selectedPanel->window;
    wmove(s, 0, 0);
    for (int i = 0; i < select->width - 1; i++) {
        waddch(s, ' ');
    }
    mvwaddnwstr(s, 0, 0, select->options[select->selected], select->width - 1);
}

void showArrow(Select* select) {
    mvwaddch(select->selectedPanel->window, 0, select->width - 1, select->active ? L'▲' : L'▼');
}

void hideArrow(Select* select) {
    if (wcslen(select->options[select->selected]) >= select->width) {
        mvwaddch(select->selectedPanel->window, 0, select->width - 1, select->options[select->selected][select->width - 1]);
    } else {
        mvwaddch(select->selectedPanel->window, 0, select->width - 1, ' ');
    }
}

void openList(Select* select) {
    PanelShow(select->listPanel);
    select->active = true;
    showArrow(select);
}

void closeList(Select* select) {
    PanelHide(select->listPanel);
    select->active = false;
    showArrow(select);
}

void SelectOnMouseClick(InteractivePanel* handle, MEVENT event) {
    Select* select = handle->holder->spec;
    if (select->active) {
        closeList(select);
    } else {
        if (select->enabled) {
            openList(select);
        }
    }
}

void ListOnMouseClick(InteractivePanel* handle, MEVENT event) {
    Select* select = handle->holder->spec;
    SelectSetSelected(select, event.y);
    openList(select);
}

void SelectShow(Component* handle) {
    Select* select = handle->spec;
    if (select->enabled) {
        wbkgd(select->selectedPanel->window, COLOR_PAIR(select->style->defaultColor));
    } else {
        wbkgd(select->selectedPanel->window, COLOR_PAIR(select->style->disabledColor));
    }
    PanelShow(select->selectedPanel);
}

void SelectHide(Component* handle) {
    Select* select = handle->spec;
    PanelHide(select->selectedPanel);
}

void SelectOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    Select* select = handle->spec;
    if (key == KEY_DOWN) {
        if (select->selected < select->count - 1) SelectSetSelected(select, select->selected + 1);
    } else if (key == KEY_UP) {
        if (select->selected > 0) SelectSetSelected(select, select->selected - 1);
    } else if (key == KEY_ENTER) {
        if (select->active) {
            closeList(select);
            DefocusComponent(handle);
        } else {
            openList(select);
        }
    }
}

bool SelectOnFocusGet(Component* handle) {
    Select* select = handle->spec;
    if (select->enabled) {
        wbkgd(select->selectedPanel->window, COLOR_PAIR(select->style->focusedColor));
        showArrow(select);
        return true;
    } else {
        return false;
    }
}

void SelectOnFocusLost(Component* handle) {
    Select* select = handle->spec;
    if (select->enabled) {
        wbkgd(select->selectedPanel->window, COLOR_PAIR(select->style->defaultColor));
        if (select->active) {
            closeList(select);
        }
        hideArrow(select);
        select->action(handle);
    } else {
        wbkgd(select->selectedPanel->window, COLOR_PAIR(select->style->disabledColor));
    }
}

Component* CreateSelect(SelectStyle* style, int x, int y, int width, int count, ...) {
    Component* handle = CreateComponent();
    Select* select = malloc(sizeof(Select));
    select->style = style;
    select->enabled = true;
    select->active = false;
    select->width = width;
    select->count = count;
    select->options = malloc(sizeof(wchar_t*) * count);
    select->action = defaultSelectEnterAction;

    InteractivePanel* listPanel = CreateInteractivePanel(handle, x, y + 1, width, count);
    wbkgd(listPanel->window, COLOR_PAIR(select->style->listColor));
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        select->options[i] =  va_arg(args, wchar_t*);
        mvwaddnwstr(listPanel->window, i, 1, select->options[i], width - 1);
    }
    va_end(args);
    listPanel->OnMouseClick = ListOnMouseClick;
    select->listPanel = listPanel;

    InteractivePanel* selectedPanel = CreateInteractivePanel(handle, x, y, width, 1);
    wbkgd(selectedPanel->window, COLOR_PAIR(select->style->defaultColor));
    selectedPanel->OnMouseClick = SelectOnMouseClick;
    select->selectedPanel = selectedPanel;

    SelectSetSelected(select, 0);
    hideArrow(select);
//    wmove(select->selectedPanel->window, 0, select->width - 1);
//    waddch(select->selectedPanel->window, L'▼');

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Select", GetNextId());

    handle->spec = select;
    handle->Show = SelectShow;
    handle->Hide = SelectHide;
    handle->OnKeyClick = SelectOnKeyClick;
    handle->OnFocusGet = SelectOnFocusGet;
    handle->OnFocusLost = SelectOnFocusLost;
    return handle;
}

void SelectSetEnabled(Component* handle, bool enabled) {
    Select* select = handle->spec;
    select->enabled = enabled;
    WINDOW* w = select->selectedPanel->window;
    if (enabled) {
        wbkgd(w, COLOR_PAIR(select->style->defaultColor));
    } else {
        wbkgd(w, COLOR_PAIR(select->style->disabledColor));
    }
}

SelectStyle* CreateSelectStyle(int defaultColor, int disabledColor, int focusedColor, int listColor, int activeItemColor) {
    SelectStyle* style = malloc(sizeof(SelectStyle));
    style->defaultColor = defaultColor;
    style->disabledColor = disabledColor;
    style->focusedColor = focusedColor;
    style->listColor = listColor;
    style->activeItemColor = activeItemColor;
    return style;
}