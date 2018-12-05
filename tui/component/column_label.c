#include "column_label.h"


void defaultOnDirectionChange(Component* handle) {
    //noop
}

void setDirection(Component* handle, SortDirection direction) {
    ColumnLabel* columnLabel = handle->spec;
    columnLabel->activeDirection = direction;
    if (columnLabel->activeDirection == NONE) {
        if (wcslen(columnLabel->text) >= columnLabel->size) {
            mvwaddch(columnLabel->panel->window, 0, columnLabel->size - 1, columnLabel->text[columnLabel->size - 1]);
        } else {
            mvwaddch(columnLabel->panel->window, 0, columnLabel->size - 1, ' ');
        }
    } else {
        mvwaddch(columnLabel->panel->window, 0, columnLabel->size - 1, columnLabel->activeDirection == ASC ? L'▲' : L'▼');
    }
}

void updateStyle(Component* handle) {
    ColumnLabel* columnLabel = handle->spec;
    if (columnLabel->activeDirection == NONE) {
        wbkgd(columnLabel->panel->window, COLOR_PAIR(columnLabel->style->defaultColor));
    } else {
        wbkgd(columnLabel->panel->window, COLOR_PAIR(columnLabel->style->activeColor));
    }
}

void ColumnLabelOnMouseClick(InteractivePanel* handle, MEVENT event) {
    if (event.bstate & BUTTON1_CLICKED || event.bstate & BUTTON1_PRESSED) {
        setDirection(handle->holder, ASC);
    } else if (event.bstate & BUTTON3_CLICKED || event.bstate & BUTTON3_PRESSED) {
        setDirection(handle->holder, DSC);
    }
}

void ColumnLabelShow(Component* handle) {
    ColumnLabel* columnLabel = handle->spec;
    updateStyle(handle);
    PanelShow(columnLabel->panel);
}

void ColumnLabelHide(Component* handle) {
    ColumnLabel* label = handle->spec;
    PanelHide(label->panel);
}

void ColumnLabelOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    ColumnLabel* columnLabel = handle->spec;
    if (key == KEY_DOWN) {
        ColumnLabelSetDirection(handle, DSC);
    } else if (key == KEY_UP) {
        ColumnLabelSetDirection(handle, ASC);
    } else if (key == KEY_ENTER) {
        DefocusComponent(handle);
    }
}


bool ColumnLabelOnFocusGet(Component* handle) {
    ColumnLabel* columnLabel = handle->spec;
    if (columnLabel->enabled) {
        wbkgd(columnLabel->panel->window, COLOR_PAIR(columnLabel->style->focusedColor));
        return true;
    } else {
        return false;
    }
}

void ColumnLabelOnFocusLost(Component* handle) {
    ColumnLabel* columnLabel = handle->spec;
    updateStyle(handle);
    if (columnLabel->activeDirection != NONE) {
        columnLabel->OnDirectionChange(handle);
    }
}

Component* CreateColumnLabel(ColumnLabelStyle* style, int x, int y, int size, wchar_t* text) {
    Component* handle = CreateComponent();
    ColumnLabel* columnLabel = malloc(sizeof(ColumnLabel));
    columnLabel->style = style;
    columnLabel->enabled = true;
    columnLabel->size = size;
    columnLabel->activeDirection = NONE;
    columnLabel->comparator = NULL;
    columnLabel->OnDirectionChange = defaultOnDirectionChange;
    columnLabel->text = malloc(sizeof(wchar_t) * (size + 1));
    wmemcpy_s(columnLabel->text, (size_t) size, text, (size_t) size); //wcscpy_s не работает

    InteractivePanel* panel = CreateInteractivePanel(handle, x, y, size, 1);
    wbkgd(panel->window, COLOR_PAIR(columnLabel->style->defaultColor));
    wmove(panel->window, 0, 0);
    waddwstr(panel->window, columnLabel->text);
    panel->OnMouseClick = ColumnLabelOnMouseClick;
    columnLabel->panel = panel;

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "ColLbl", GetNextId());

    handle->spec = columnLabel;
    handle->Show = ColumnLabelShow;
    handle->Hide = ColumnLabelHide;
    handle->OnKeyClick = ColumnLabelOnKeyClick;
    handle->OnFocusGet = ColumnLabelOnFocusGet;
    handle->OnFocusLost = ColumnLabelOnFocusLost;
    return handle;
}

void ColumnLabelSetEnabled(Component* handle, bool enabled) {
    ColumnLabel* columnLabel = handle->spec;
    columnLabel->enabled = enabled;
    if (enabled) {
        updateStyle(handle);
    } else {
        wbkgd(columnLabel->panel->window, COLOR_PAIR(columnLabel->style->disabledColor));
        DefocusComponent(handle);
    }
}

void ColumnLabelSetDirection(Component* handle, SortDirection direction) {
    setDirection(handle, direction);
    updateStyle(handle);
}

ColumnLabelStyle* CreateColumnLabelStyle(int defaultColor, int focusedColor, int activeColor, int disabledColor) {
    ColumnLabelStyle* style = malloc(sizeof(ColumnLabelStyle));
    style->defaultColor = defaultColor;
    style->focusedColor = focusedColor;
    style->activeColor = activeColor;
    style->disabledColor = disabledColor;
    return style;
}