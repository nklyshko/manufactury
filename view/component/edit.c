#include <src/log.h>
#include "edit.h"

#define RU_BEGIN 1040
#define RU_END   1103
#define EN_BEGIN 65
#define EN_END   122
#define NUM_BEGIN 48
#define NUM_END   57

#ifdef KEY_BACKSPACE
# undef KEY_BACKSPACE
#endif
#define KEY_BACKSPACE 8

#ifdef KEY_HOME
# undef KEY_HOME
#endif
#define KEY_HOME 60609

#ifdef KEY_END
# undef KEY_END
#endif
#define KEY_END 60615

#define KEY_DELETE KEY_DC
#define KEY_INSERT KEY_IC


bool replaceMode = FALSE;

void updateCursor(Edit* edit) {
    movecurs(edit->panelEditField->panel, edit->pos, 0);
    wmove(edit->panelEditField->window, 0, edit->pos);
}

void SetPos(Edit* edit, int pos) {
    if (pos <= edit->length) {
        edit->pos = pos;
        updateCursor(edit);
    }
}

void deleteChar(wchar_t* s, int pos) {
    memmove(s + pos, s + pos + 1, wcslen(s) - pos);
}

void insertChar(wchar_t* s, int pos, wchar_t c) {
    memmove(s + pos + 1, //width of space = 1
            s + pos,
            wcslen(s) + 1 - pos); // +1 - string always ends with \0, but len not includes it
    s[pos] = c;
}

bool allowedSymbol(int s) {
    return (s >= NUM_BEGIN && s <= NUM_END) || (s >= EN_BEGIN && s <= EN_END) || (s >= RU_BEGIN && s <= RU_END) || s == 1025 || s == 1105;
}

void EditOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    Edit* edit = handle->spec;
    //TODO: Поддержка Копировать/Ctrl+C, Вставить/Ctrl+V, Вырезать/Ctrl+X
    log_debug("Edit key %d", key);
    if (allowedSymbol(key)) {
        wchar_t ch = (wchar_t) key;
        if (replaceMode) {
            log_debug("CUR NULL %s", edit->data[edit->pos] == '\0' ? "true" : "false");
            if (edit->data[edit->pos] == '\0') {
                if (edit->length < edit->size) {
                    edit->data[edit->pos + 1] = '\0';
                    edit->length++;
                    edit->data[edit->pos] = ch;
                    waddch(edit->panelEditField->window, ch);
                    SetPos(edit, edit->pos + 1);
                }
            } else {
                edit->data[edit->pos] = ch;
                waddch(edit->panelEditField->window, ch);
                SetPos(edit, edit->pos + 1);
            }
        } else if (edit->length < edit->size) {
            insertChar(edit->data, edit->pos, ch);
            edit->length++;
            winsch(edit->panelEditField->window, ch);
            SetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_BACKSPACE) {
        if (edit->length > 0) {
            if (edit->pos > 0) {
                SetPos(edit, edit->pos - 1);
                wdelch(edit->panelEditField->window);
                deleteChar(edit->data, edit->pos);
                edit->length--;
            }
        }
    } else if (key == KEY_DELETE) {
        if (edit->pos >= 0 && edit->pos < edit->length) {
            wdelch(edit->panelEditField->window);
            deleteChar(edit->data, edit->pos);
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
            SetPos(edit, edit->pos - 1);
        }
    } else if (key == KEY_RIGHT) {
        if (edit->pos < edit->size) {
            SetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_HOME) {
        SetPos(edit, 0);
    } else if (key == KEY_END) {
        SetPos(edit, edit->length);
    }
    log_debug("CUR LENG: %d", wcslen(edit->data));
}

void EditOnFocusGet(Component* handle) {
    replaceMode = FALSE;
    curs_set(1);
    Edit* edit = handle->spec;
    SetPos(edit, edit->length); //reset position to end of line
    //updateCursor(edit);
}

void EditOnFocusLost(Component* handle) {
    curs_set(0);
    move(0, 0);
}

Component* CreateEdit(int x, int y, int size) {
    log_debug("Create Edit");

    Component* component = CreateComponent();
    InteractivePanel* panelEditField = CreateInteractivePanel(component, x, y, size, 1);

    Edit* edit = malloc(sizeof(Edit));
    edit->size = size;
    edit->pos = 0;
    edit->length = 0;
    edit->data = malloc(sizeof(wchar_t) * (size + 1));
    edit->data[0] = '\0';
    edit->panelEditField = panelEditField;

    component->OnKeyClick = EditOnKeyClick;
    component->OnFocusGet = EditOnFocusGet;
    component->OnFocusLost = EditOnFocusLost;
    component->spec = edit;
    component->id = "Edit";
    return component;
}
