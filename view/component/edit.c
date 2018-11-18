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

#ifdef KEY_ENTER
# undef KEY_ENTER
#endif
#define KEY_ENTER 10

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
    show_panel(edit->panelEditField->panel);
}

void EditHide(Component* handle) {
    Edit* edit = handle->spec;
    hide_panel(edit->panelEditField->panel);
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
                    waddch(edit->panelEditField->window, ch);
                    SetPos(edit, edit->pos + 1);
                }
            } else {
                edit->data[edit->pos] = ch;
                waddch(edit->panelEditField->window, ch);
                SetPos(edit, edit->pos + 1);
            }
        } else if (edit->length < edit->size) {
            insertChar(edit->data, edit->length, edit->pos, ch);
            edit->length++;
            winsch(edit->panelEditField->window, ch);
            SetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_BACKSPACE) {
        if (edit->length > 0) {
            if (edit->pos > 0) {
                SetPos(edit, edit->pos - 1);
                wdelch(edit->panelEditField->window);
                deleteChar(edit->data, edit->length, edit->pos);
                edit->length--;
            }
        }
    } else if (key == KEY_DELETE) {
        if (edit->pos >= 0 && edit->pos < edit->length) {
            wdelch(edit->panelEditField->window);
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
    } else if (key == KEY_ENTER) {

    }
}

bool EditOnFocusGet(Component* handle) {
    replaceMode = FALSE;
    curs_set(1);
    Edit* edit = handle->spec;
    SetPos(edit, edit->length); //установить курсор в конец строки
    return true;
}

void EditOnFocusLost(Component* handle) {
    curs_set(0);
    move(0, 0);
}

Component* CreateEdit(int x, int y, int size) {
    Component* handle = CreateComponent();
    InteractivePanel* panelEditField = CreateInteractivePanel(handle, x, y, size, 1);

    Edit* edit = malloc(sizeof(Edit));
    edit->size = size;
    edit->pos = 0;
    edit->length = 0;
    edit->data = malloc((size + 1) * sizeof(wchar_t));
    edit->data[0] = L'\0';
    edit->panelEditField = panelEditField;


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
