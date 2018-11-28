#include <list.h>
#include <curses.h>
#include <src/log.h>
#include <key_codes.h>
#include "hotkey.h"

#define A_CODE 0x01 //первая буква в алфавите
#define Z_CODE 0x1a //последняя буква в алфавите

typedef struct HotKeyAction HotKeyAction;

struct HotKeyAction{
    HotKey* hotKey;
    void (* action)(void);
};

List* registeredHotKeys;
void (* hotKeyEventHandler)(HotKey* hotKey);

bool InitHotKeyHandler(void (* eventHandler)(HotKey* hotKey)) {
    hotKeyEventHandler = eventHandler;
    if (list_new(&registeredHotKeys) == CC_ERR_ALLOC) {
        return FALSE;
    }
    return TRUE;
}

HotKey* CreateHotKey(char symbol, unsigned long modifiers) {
    HotKey* hotKey = malloc(sizeof(HotKey));
    hotKey->key = (int) symbol - HOTKEY_OFFSET;
    hotKey->modifiers = modifiers;
    hotKey->title = malloc(sizeof(wchar_t) * 13);
    hotKey->title[0] = (wchar_t) (hotKey->key + HOTKEY_OFFSET);
    hotKey->title[1] = L'\0';

    if (hotKey->modifiers & KEY_SHIFT) {
        wmemmove(hotKey->title + 2, hotKey->title, wcslen(hotKey->title) + 1);
        hotKey->title[0] = L'↑';
        hotKey->title[1] = L'+';
    }
    if (hotKey->modifiers & KEY_ALT) {
        wmemmove(hotKey->title + 4, hotKey->title, wcslen(hotKey->title) + 1);
        hotKey->title[0] = L'A';
        hotKey->title[1] = L'l';
        hotKey->title[2] = L't';
        hotKey->title[3] = L'+';
    }
    if (hotKey->modifiers & KEY_CTRL) {
        wmemmove(hotKey->title + 5, hotKey->title, wcslen(hotKey->title) + 1);
        hotKey->title[0] = L'C';
        hotKey->title[1] = L't';
        hotKey->title[2] = L'r';
        hotKey->title[3] = L'l';
        hotKey->title[4] = L'+';
    }
    return hotKey;
}

bool TestHotKey(HotKey* hotKey, int ch, unsigned long modifiers) {
    return hotKey->key == ch && hotKey->modifiers == modifiers;
}

void RegisterHotKeyAction(HotKey* hotKey, void (* action)(void)) {
    HotKeyAction* hotKeyAction = malloc(sizeof(HotKeyAction));
    hotKeyAction->hotKey = hotKey;
    hotKeyAction->action = action;
    list_add(registeredHotKeys, hotKeyAction);
}

bool HandleHotKeyEvent(int key, unsigned long modifiers) {
    if (!(key >= A_CODE && key <= Z_CODE) && !(key >= A_CODE + HOTKEY_OFFSET && key <= Z_CODE + HOTKEY_OFFSET)) return FALSE;
    ListIter li;
    list_iter_init(&li, registeredHotKeys);
    HotKeyAction* hotKeyAction;
    while (list_iter_next(&li, (void**) &hotKeyAction) != CC_ITER_END) {
        HotKey* hotKey = hotKeyAction->hotKey;
        if ((hotKey->key == key || hotKey->key + HOTKEY_OFFSET == key) && hotKey->modifiers == modifiers) {
            hotKeyAction->action();
            if (hotKeyEventHandler != NULL) {
                hotKeyEventHandler(hotKey);
            }
            return TRUE;
        }
    }
    return FALSE;
}