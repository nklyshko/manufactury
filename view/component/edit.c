#include <src/log.h>
#include "edit.h"

#define RU_BEGIN 1040
#define RU_END   1103
#define EN_BEGIN 65
#define EN_END   122
#define NUM_BEGIN 48
#define NUM_END   57


void DefaultEnterAction(Component* handle) {
    //noop
}

bool replaceMode = FALSE;

void updateCursor(Edit* edit) {
    movecurs(edit->panel->panel, edit->pos, 0);
    wmove(edit->panel->window, 0, edit->pos);
}

void EditSetPos(Edit* edit, int pos) {
    if (pos <= edit->length) {
        edit->pos = pos;
        updateCursor(edit);
    }
}

void deleteChar(wchar_t* s, int length, int pos) {
    wmemmove(s + pos, s + pos + 1, (size_t) (length - pos));
}

void insertChar(wchar_t* s, int length, int pos, wchar_t c) {
    wmemmove(s + pos + 1, //width of space = 1
            s + pos,
            (size_t) (length + 1 - pos)); // +1 - string always ends with \0, but len not includes it
    s[pos] = c;
}

bool allowedSymbol(int s) {
    return (s >= NUM_BEGIN && s <= NUM_END) || (s >= EN_BEGIN && s <= EN_END) || (s >= RU_BEGIN && s <= RU_END) || s == 1025 || s == 1105;
}

void EditShow(Component* handle) {
    Edit* edit = handle->spec;
    wbkgd(edit->panel->window, COLOR_PAIR(edit->style->defaultColor));
    PanelShow(edit->panel);
}

void EditHide(Component* handle) {
    Edit* edit = handle->spec;
    PanelHide(edit->panel);
}

void EditOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    Edit* edit = handle->spec;
    //TODO: Поддержка Копировать/Ctrl+C, Вставить/Ctrl+V, Вырезать/Ctrl+X
    if (allowedSymbol(key)) {
        wchar_t ch = (wchar_t) key;
        if (replaceMode) {
            if (edit->pos == edit->length) {
                if (edit->length < edit->size) {
                    edit->data[edit->pos] = ch;
                    edit->length++;
                    edit->data[edit->length] = L'\0';
                    waddch(edit->panel->window, ch);
                    EditSetPos(edit, edit->pos + 1);
                }
            } else {
                edit->data[edit->pos] = ch;
                waddch(edit->panel->window, ch);
                EditSetPos(edit, edit->pos + 1);
            }
        } else if (edit->length < edit->size) {
            insertChar(edit->data, edit->length, edit->pos, ch);
            edit->length++;
            winsch(edit->panel->window, ch);
            EditSetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_BACKSPACE) {
        if (edit->length > 0) {
            if (edit->pos > 0) {
                EditSetPos(edit, edit->pos - 1);
                wdelch(edit->panel->window);
                deleteChar(edit->data, edit->length, edit->pos);
                edit->length--;
            }
        }
    } else if (key == KEY_DELETE) {
        if (edit->pos >= 0 && edit->pos < edit->length) {
            wdelch(edit->panel->window);
            deleteChar(edit->data, edit->length, edit->pos);
            edit->length--;
        }
    } else if (key == KEY_INSERT) {
        if (replaceMode) {
            replaceMode = FALSE;
            curs_set(1); //underline
        } else {
            replaceMode = TRUE;
            curs_set(2); //full block
        }
    } else if (key == KEY_LEFT) {
        if (edit->pos > 0) {
            EditSetPos(edit, edit->pos - 1);
        }
    } else if (key == KEY_RIGHT) {
        if (edit->pos < edit->size) {
            EditSetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_HOME) {
        EditSetPos(edit, 0);
    } else if (key == KEY_END) {
        EditSetPos(edit, edit->length);
    } else if (key == KEY_ENTER) {
        FocusComponent(NULL);
        edit->action(handle);
    }
}

bool EditOnFocusGet(Component* handle) {
    replaceMode = FALSE;
    curs_set(1);
    Edit* edit = handle->spec;
    wbkgd(edit->panel->window, COLOR_PAIR(edit->style->activeColor));
    EditSetPos(edit, edit->length); //установить курсор в конец строки
    return true;
}

void EditOnFocusLost(Component* handle) {
    curs_set(0);
    move(0, 0);
    Edit* edit = handle->spec;
    wbkgd(edit->panel->window, COLOR_PAIR(edit->style->defaultColor));
}

Component* CreateEdit(EditStyle* style, int x, int y, int size) {
    Component* handle = CreateComponent();
    Edit* edit = malloc(sizeof(Edit));
    edit->style = style;
    edit->size = size;
    edit->pos = 0;
    edit->length = 0;
    edit->data = malloc((size + 1) * sizeof(wchar_t));
    edit->data[0] = L'\0';
    edit->action = DefaultEnterAction;

    InteractivePanel* panel = CreateInteractivePanel(handle, x, y, size + 1, 1);
    edit->panel = panel;

    handle->spec = edit;
    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Edit", GetNextId());

    handle->Show = EditShow;
    handle->Hide = EditHide;
    handle->OnKeyClick = EditOnKeyClick;
    handle->OnFocusGet = EditOnFocusGet;
    handle->OnFocusLost = EditOnFocusLost;
    return handle;
}

void EditSetEnterAction(Component* handle, void (* action)(Component* handle)) {
    Edit* edit = handle->spec;
    edit->action = action;
}

EditStyle* CreateEditStyle(int defaultColor, int activeColor) {
    EditStyle* style = malloc(sizeof(EditStyle));
    style->defaultColor = defaultColor;
    style->activeColor = activeColor;
    return style;
}
