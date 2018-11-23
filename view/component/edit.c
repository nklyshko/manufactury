#include <src/log.h>
#include <global.h>
#include <view/hotkey.h>
#include "edit.h"

#define RU_BEGIN 1040
#define RU_END   1103
#define EN_BEGIN 65
#define EN_END   122
#define NUM_BEGIN 48
#define NUM_END   57


void defaultOnValueEnter(Component* handle) {
    //noop
}

bool replaceMode = FALSE;

void updateCursor(Edit* edit) {
    movecurs(edit->panel->panel, edit->pos, 0);
    wmove(edit->panel->window, 0, edit->pos);
}

void editSetPos(Edit* edit, int pos) {
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
    if (edit->enabled) {
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->defaultColor));
    } else {
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->disabledColor));
    }
    PanelShow(edit->panel);
}

void EditHide(Component* handle) {
    Edit* edit = handle->spec;
    PanelHide(edit->panel);
}

void EditOnKeyClick(Component* handle, int key, unsigned long modifiers) {
    Edit* edit = handle->spec;
    //TODO: Поддержка Копировать/Ctrl+C, Вставить/Ctrl+V, Вырезать/Ctrl+X
//    bool selectMode = false;
//    if (modifiers == KEY_SHIFT) selectMode = true;
//    if (modifiers == KEY_CTRL) {
//        char *ptr = NULL;
//        long i, length = 0;
//        switch (key) {
//            case 'C' - HOTKEY_OFFSET:
//                if (PDC_setclipboard(text, (long)strlen(text) == PDC_CLIP_SUCCESS) {
//
//                }
//                break;
//            case 'V' - HOTKEY_OFFSET:
//                if (PDC_getclipboard(&ptr, &length) == PDC_CLIP_SUCCESS) {
//
//                }
//                break;
//            case 'X' - HOTKEY_OFFSET:
//                break;
//            default:
//                break;
//        } else
    if (allowedSymbol(key)) {
        wchar_t ch = (wchar_t) key;
        if (replaceMode) {
            if (edit->pos == edit->length) {
                if (edit->length < edit->size) {
                    edit->value[edit->pos] = ch;
                    edit->length++;
                    edit->value[edit->length] = L'\0';
                    waddch(edit->panel->window, ch);
                    editSetPos(edit, edit->pos + 1);
                }
            } else {
                edit->value[edit->pos] = ch;
                waddch(edit->panel->window, ch);
                editSetPos(edit, edit->pos + 1);
            }
        } else if (edit->length < edit->size) {
            insertChar(edit->value, edit->length, edit->pos, ch);
            edit->length++;
            winsch(edit->panel->window, ch);
            editSetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_BACKSPACE) {
        if (edit->length > 0) {
            if (edit->pos > 0) {
                editSetPos(edit, edit->pos - 1);
                wdelch(edit->panel->window);
                deleteChar(edit->value, edit->length, edit->pos);
                edit->length--;
            }
        }
    } else if (key == KEY_DELETE) {
        if (edit->pos >= 0 && edit->pos < edit->length) {
            wdelch(edit->panel->window);
            deleteChar(edit->value, edit->length, edit->pos);
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
//            if (selectMode) {
//                if (edit->selected > 0) {
//                    edit->selected--;
//                }
//            }
            editSetPos(edit, edit->pos - 1);
        }
    } else if (key == KEY_RIGHT) {
        if (edit->pos < edit->size) {
            editSetPos(edit, edit->pos + 1);
        }
    } else if (key == KEY_HOME) {
        editSetPos(edit, 0);
    } else if (key == KEY_END) {
        editSetPos(edit, edit->length);
    } else if (key == KEY_ENTER) {
        DefocusComponent(handle);
    }
}

bool EditOnFocusGet(Component* handle) {
    Edit* edit = handle->spec;
    if (edit->enabled) {
        replaceMode = FALSE;
        curs_set(1);
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->activeColor));
        editSetPos(edit, edit->length); //установить курсор в конец строки
        return true;
    } else {
        return false;
    }
}

void EditOnFocusLost(Component* handle) {
    curs_set(0);
    move(0, 0);
    Edit* edit = handle->spec;
    if (edit->enabled) {
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->defaultColor));
    } else {
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->disabledColor));
    }
    edit->OnValueEnter(handle);
}

Component* CreateEdit(EditStyle* style, int x, int y, int size) {
    Component* handle = CreateComponent();
    Edit* edit = malloc(sizeof(Edit));
    edit->style = style;
    edit->enabled = true;
    edit->size = size;
    edit->pos = 0;
    edit->selected = 0;
    edit->length = 0;
    edit->value = malloc((size + 1) * sizeof(wchar_t));
    edit->value[0] = L'\0';
    edit->OnValueEnter = defaultOnValueEnter;

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

void EditSetValue(Component* handle, wchar_t* value) {
    Edit* edit = handle->spec;
    wmemcpy_s(edit->value, (size_t) edit->size, value, (size_t) edit->size); //wcscpy_s не работает
    wclear(edit->panel->window);
    mvwaddwstr(edit->panel->window, 0, 0, edit->value);
}

void EditSetEnabled(Component* handle, bool enabled) {
    Edit* edit = handle->spec;
    edit->enabled = enabled;
    if (enabled) {
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->defaultColor));
    } else {
        wbkgd(edit->panel->window, COLOR_PAIR(edit->style->disabledColor));
        DefocusComponent(handle);
    }
}

void EditSetEnterAction(Component* handle, void (* OnValueEnter)(Component* handle)) {
    Edit* edit = handle->spec;
    edit->OnValueEnter = OnValueEnter;
}

EditStyle* CreateEditStyle(int defaultColor, int disabledColor, int activeColor) {
    EditStyle* style = malloc(sizeof(EditStyle));
    style->defaultColor = defaultColor;
    style->disabledColor = disabledColor;
    style->activeColor = activeColor;
    return style;
}
